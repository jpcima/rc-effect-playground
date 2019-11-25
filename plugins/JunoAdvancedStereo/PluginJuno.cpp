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
#include "chorus_advanced_stereo.cxx"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginJuno::PluginJuno()
    : Plugin(paramCount, presetCount, stateCount),
      fChorus(new faustChorusAdvancedStereo)
{
    sampleRateChanged(getSampleRate());
    if (presetCount > 0) {
        loadProgram(0);
    }
    else {
        for (unsigned i = 0; i < paramCount; ++i) {
            Parameter p;
            InitParameter(i, p);
            setParameterValue(i, p.ranges.def);
        }
    }
}

PluginJuno::~PluginJuno()
{
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
    fChorus->instanceConstants(newSampleRate);
}

/**
  Get the current value of a parameter.
*/
float PluginJuno::getParameterValue(uint32_t index) const {
    float value;

    switch (index) {
    case pIdBypass:
        value = *fChorus->fControlBypass;
        break;
    case pIdLfoRate:
        value = *fChorus->fControlLfoRate;
        break;
    case pIdLfoShape:
        value = *fChorus->fControlLfoShape;
        break;
    case pIdLfoPhase:
        value = *fChorus->fControlLfoPhase;
        break;
    case pIdDelayDomain1:
        value = *fChorus->fControlDelayDomain1;
        break;
    case pIdDelayDomain2:
        value = *fChorus->fControlDelayDomain2;
        break;
    case pIdPresence:
        value = *fChorus->fControlPresence;
        break;
    default:
        value = 0;
        DISTRHO_SAFE_ASSERT(false);
    }

    return value;
}

/**
  Change a parameter value.
*/
void PluginJuno::setParameterValue(uint32_t index, float value) {
    switch (index) {
    case pIdBypass:
        *fChorus->fControlBypass = value;
        break;
    case pIdLfoRate:
        *fChorus->fControlLfoRate = value;
        break;
    case pIdLfoShape:
        *fChorus->fControlLfoShape = value;
        break;
    case pIdLfoPhase:
        *fChorus->fControlLfoPhase = value;
        break;
    case pIdDelayDomain1:
        *fChorus->fControlDelayDomain1 = value;
        break;
    case pIdDelayDomain2:
        *fChorus->fControlDelayDomain2 = value;
        break;
    case pIdPresence:
        *fChorus->fControlPresence = value;
        break;
    default:
        DISTRHO_SAFE_ASSERT(false);
    }
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
    fChorus->instanceClear();
}



void PluginJuno::run(const float** inputs, float** outputs, uint32_t frames) {
    fChorus->compute(frames, const_cast<float**>(inputs), outputs);
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginJuno();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
