#!/usr/bin/python
#
# This scripts extracts instantaneous delay times from a sound sample of
# chorused sawtooth.
#
# TODO improve the quality of detection
#
# Usage example: analyze.py juno60-1.wav
#

import scipy.io.wavfile
import scipy.signal
import sys

def process_channel(data, samplerate):
    result = []

    # locate peak positions found within neighborhoods of certain widths
    # TODO should express the width in time units, new input recordings having varying SR
    peaks, props = scipy.signal.find_peaks(data, width=20)

    count = len(peaks)

    nth = 0
    while nth < count - 1:
        pos1 = peaks[nth]
        pos2 = peaks[nth + 1]

        # expect to find a high peak, and then a lower peak immediately following

        if data[pos1] < data[pos2]:
            nth += 1
        else:
            result.append((pos1 / samplerate, (pos2 - pos1) / samplerate))
            nth += 2

    return result

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.stderr.write('Incorrect arguments\n')
        sys.exit(1)

    soundfile = sys.argv[1]

    samplerate, data = scipy.io.wavfile.read(soundfile)
    numchannels = len(data[1])

    # scale it to unity
    data = data / float(1 << 15)

    # print(data[:,0])

    delays = [None] * numchannels
    for i in range(numchannels):
        delays[i] = process_channel(data[:, i], samplerate)

        sys.stderr.write('Channel %d: found %d results\n' % (i + 1, len(delays[i])))

        f = open('channel%d.dat' % (i + 1), 'w')
        for (t, d1) in delays[i]:
            f.write(('%e %e\n') % (t, d1))
        f.close()
