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

#ifndef PLUGIN_JUNO_H
#define PLUGIN_JUNO_H

#include "DistrhoPlugin.hpp"
#include "Controls.hpp"
#include "bbd_line.h"
#include <array>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PluginJuno : public Plugin {
public:
    PluginJuno();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "Juno";
    }

    const char* getDescription() const override {
        return "Chorus";
    }

    const char* getMaker() const noexcept override {
        return "example.com";
    }

    const char* getHomePage() const override {
        return "https://example.com/plugins/juno";
    }

    const char* getLicense() const noexcept override {
        return "https://spdx.org/licenses/MIT";
    }

    uint32_t getVersion() const noexcept override {
        return d_version(0, 1, 0);
    }

    // Go to:
    //
    // http://service.steinberg.de/databases/plugin.nsf/plugIn
    //
    // Get a proper plugin UID and fill it in here!
    int64_t getUniqueId() const noexcept override {
        return d_cconst('a', 'b', 'c', 'd');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Optional

    // Optional callback to inform the plugin about a sample rate change.
    void sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;

    void run(const float**, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------
    void processWithinBufferLimit(const float* in, float* outL, float* outR, uint32_t frames);

    // -------------------------------------------------------------------

private:
    float    fParams[paramCount];
    double   fSampleRate;

    float fLfoPhase = 0;
    std::array<BBD_Line, 2> fDelays;

    enum { kDelayChipStages = 256 }; /* see MN3009 */

    enum { kBufferLimit = 256 }; /* maximum samples in one run */

    enum LfoType {
        kLfoTriangle,
        kLfoSine,
    };

    // /* Chorus fixed constants (TODO set correct values; these from Dimension-D ratings) */
    // static constexpr float kLineAvgDelay = 10e-3;
    // static constexpr float kLineDelayModRange = 2e-3;

    /* Chorus fixed constants (TODO set correct values; generic chorus ratings) */
    // static constexpr float kLineAvgDelay = 35e-3;
    // static constexpr float kLineDelayModRange = 20e-3;

    /*
      Juno 6
      ======

      BBDs: 2x MN3009

      LFOs: 1LFO with three settings
      * I = 100% amount, 0.4Hz, triangle
      * II = 100% amount, 0.6Hz, triangle
      * I + II = 25% amount, 8Hz, sine like
     */

    // static constexpr float kLfoSpeed = 0.4;
    // static constexpr float kLfoAmplitude = 1.0;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginJuno)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_JUNO_H
