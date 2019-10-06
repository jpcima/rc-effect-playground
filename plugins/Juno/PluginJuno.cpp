/*
 * Juno audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2019 Joe Doe <joe.doe@example.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "PluginJuno.hpp"
#include "bbd_filter.h"
#include <cstring>
#include <cmath>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginJuno::PluginJuno()
    : Plugin(paramCount, presetCount, stateCount)
{
    sampleRateChanged(getSampleRate());
    if (presetCount > 0) {
        loadProgram(0);
    }
    else {
        for (unsigned i = 0; i < paramCount; ++i) {
            Parameter p;
            InitParameter(i, p);
            fParams[i] = p.ranges.def;
        }
    }
}

// -----------------------------------------------------------------------
// Init

void PluginJuno::initParameter(uint32_t index, Parameter& parameter) {
    InitParameter(index, parameter);
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginJuno::initProgramName(uint32_t index, String& programName) {
    DISTRHO_SAFE_ASSERT_RETURN(index < presetCount,);

    programName = factoryPresets[index].name;
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginJuno::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;

    for (BBD_Line &del : fDelays)
        del.setup(newSampleRate, kDelayChipStages, bbd_fin_j60, bbd_fout_j60);
}

/**
  Get the current value of a parameter.
*/
float PluginJuno::getParameterValue(uint32_t index) const {
    DISTRHO_SAFE_ASSERT_RETURN(index < paramCount, 0);

    return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginJuno::setParameterValue(uint32_t index, float value) {
    DISTRHO_SAFE_ASSERT_RETURN(index < paramCount,);

    fParams[index] = value;
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginJuno::loadProgram(uint32_t index) {
    DISTRHO_SAFE_ASSERT_RETURN(index < presetCount,);

    for (int i=0; i < paramCount; i++) {
        setParameterValue(i, factoryPresets[index].params[i]);
    }
}

// -----------------------------------------------------------------------
// Process

void PluginJuno::activate() {
    for (BBD_Line &del : fDelays)
        del.clear();
}



void PluginJuno::run(const float** inputs, float** outputs, uint32_t frames) {
    const float* in = inputs[0];
    float* outL = outputs[0];
    float* outR = outputs[1];

    if (fParams[pIdBypass] > 0.5f) {
        memcpy(outL, in, frames * sizeof(float));
        memcpy(outR, in, frames * sizeof(float));
        return;
    }

    uint32_t frameIndex = 0;
    while (frameIndex < frames) {
        uint32_t count = std::min(frames - frameIndex, (uint32_t)kBufferLimit);
        processWithinBufferLimit(in + frameIndex, outL + frameIndex, outR + frameIndex, count);
        frameIndex += count;
    }
}

// -----------------------------------------------------------------------

static inline float triangle(float x) /* [0:1] → [-1:+1] */
{
    return (x<0.5f) ? (-1+4*x) : (3-4*x);
}

static inline float wrap(float x)
{
    return x - (int)x;
}

void PluginJuno::processWithinBufferLimit(const float* in, float* outL, float* outR, uint32_t frames)
{
    /*XXX Delay characteristic from parameters, experiment only*/
    const float kLineAvgDelay = fParams[pIdLineDelay] * 1e-3;
    const float kLineDelayModRange = kLineAvgDelay * fParams[pIdDelayModAmount];

    /*XXX LOF characteristic from parameters, experiment only*/
    const float kLfoSpeed = fParams[pIdLfoSpeed];
    const float kLfoAmplitude = fParams[pIdLfoAmplitude];

    //--------------------------------------------------------------------------

    const float samplePeriod = 1.0f / fSampleRate;
    const float lfoIncr = kLfoSpeed * samplePeriod;
    const float gainDry = std::pow(10.0f, fParams[pIdDry] * 0.05f);
    const float gainWet = std::pow(10.0f, fParams[pIdWet] * 0.05f);

    float lfoPhase = fLfoPhase;

    float clock1[kBufferLimit];
    float clock2[kBufferLimit];

    ///
    // float minClock = samplePeriod *
    //     BBD_Line::hz_rate_for_delay(kLineAvgDelay - kLfoAmplitude * kLineDelayModRange, kDelayChipStages);
    // float maxClock = samplePeriod *
    //     BBD_Line::hz_rate_for_delay(kLineAvgDelay + kLfoAmplitude * kLineDelayModRange, kDelayChipStages);
    ///

    for (unsigned i = 0; i < frames; ++i) {
        float lfo1 = kLfoAmplitude * triangle(lfoPhase);
        float lfo2 = kLfoAmplitude * triangle(wrap(lfoPhase + 0.5));

        clock1[i] = samplePeriod *
            BBD_Line::hz_rate_for_delay(kLineAvgDelay + lfo1 * kLineDelayModRange, kDelayChipStages);
        clock2[i] = samplePeriod *
            BBD_Line::hz_rate_for_delay(kLineAvgDelay + lfo2 * kLineDelayModRange, kDelayChipStages);

        // clock1[i] = (0.5 * (maxClock + minClock)) + lfo1 * (0.5 * (maxClock - minClock));
        // clock2[i] = (0.5 * (maxClock + minClock)) + lfo2 * (0.5 * (maxClock - minClock));

        lfoPhase = wrap(lfoPhase + lfoIncr);
    }

    float delayed1[kBufferLimit];
    float delayed2[kBufferLimit];

    fDelays[0].process(frames, in, delayed1, clock1);
    fDelays[1].process(frames, in, delayed2, clock2);

    for (unsigned i = 0; i < frames; ++i) {
        outL[i] = gainDry * in[i] + gainWet * delayed1[i];
        outR[i] = gainDry * in[i] + gainWet * delayed2[i];
    }

    fLfoPhase = lfoPhase;
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginJuno();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
