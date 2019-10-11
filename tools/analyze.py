#!/usr/bin/python
#
# This scripts extracts instantaneous delay times from a sound sample of
# chorused sawtooth.
#
# TODO it doesn't return precise output, check for a way to improve it.
#
# Usage example: analyze.py juno60-1.wav
#

import scipy.io.wavfile
import scipy.signal
import sys

def process_channel(data, samplerate):
    result = []

    # TODO tweak me, the reliability of the peak detector
    peaks, props = scipy.signal.find_peaks(data, width=60)

    count = len(peaks)

    # peak index which is analyzed currently
    nth = 0
    # index of 'top' peak, the edge of the sawtooth of non-delayed signal
    top = -1
    # index of top peaks of 1 or 2 delay images (if 2 delays have near peaks
    # at particular instants, can't distinguish them, so it will have 1)
    sub = []
    # the height over which a peak is taken to be from the main signal,
    # not one of its delays
    height_thr = 0.1

    while nth < count:
        pos = peaks[nth]
        height = data[pos]

        if height > height_thr:
            # we will enter analysis of a new period

            if top != -1:
                # proceed to end analyzing the former
                nsub = len(sub)
                if nsub > 2:
                    sys.stderr.write('Anomaly: too many delay peaks found; try readjusting. (%s: %s)\n' % (peaks[top], list(map(lambda x: peaks[x], sub))))
                elif nsub == 0:
                    pass
                    #sys.stderr.write('Anomaly: no delay peaks found; try readjusting. (%s)\n' % (peaks[top]))
                else:
                    if nsub == 1:
                        # they were too close of each other; record them as equal
                        sub = [sub[0], sub[0]]
                    result.append((peaks[top] / samplerate,
                                   (peaks[sub[0]] - peaks[top]) / samplerate,
                                   (peaks[sub[1]] - peaks[top]) / samplerate))

            # proceed to start analyzing next period
            top = nth
            sub = []

        else:
            # it's a delay image of a main signal
            sub.append(nth)

        nth += 1

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
        for (t, d1, d2) in delays[i]:
            f.write(('%e %e %e\n') % (t, d1, d2))
        f.close()
