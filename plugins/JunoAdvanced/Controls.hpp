#pragma once
#include "DistrhoPlugin.hpp"

enum Parameters {
    pIdBypass,
    pIdLfoRate,
    pIdLfoShape,
    pIdLfoPhase,
    pIdDelayDomain1,
    pIdDelayDomain2,
    pIdPresence,
    paramCount
};

enum States {
    stateCount
};

struct Preset {
    const char* name;
    float params[paramCount];
};

[[gnu::unused]]
static const Preset factoryPresets[] = {
    {
        "Juno 60 (I)",
        {
            0.0,   // bypass
            0.513, // lfo_rate
            0.0,   // lfo_shape
            180.0, // lfo_phase
            1.54,  // delay_domain1
            5.15,  // delay_domain2
            0.0,   // presence
        }
    },

    {
        "Juno 60 (II)",
        {
            0.0,   // bypass
            0.863, // lfo_rate
            0.0,   // lfo_shape
            180.0, // lfo_phase
            1.54,  // delay_domain1
            5.15,  // delay_domain2
            0.0,   // presence
        }
    },


    {
        "Juno 60 (I+II)",
        {
            0.0,   // bypass
            8.75,  // lfo_rate
            0.0,   // lfo_shape
            0.0,   // lfo_phase
            3.22,  // delay_domain1
            3.56,  // delay_domain2
            0.0,   // presence
        }
    },

    {
        "JX-3P",
        {
            0.0,   // bypass
            0.48,  // lfo_rate
            0.0,   // lfo_shape
            180.0, // lfo_phase
            1.54,  // delay_domain1
            5.15,  // delay_domain2
            0.0,   // presence
        }
    },

    {
        "JX-03",
        {
            0.0,   // bypass
            0.462, // lfo_rate
            0.5,   // lfo_shape
            180.0, // lfo_phase
            1.54,  // delay_domain1
            5.15,  // delay_domain2
            0.0,   // presence
        }
    },
};

[[gnu::unused]]
static constexpr uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

void InitParameter(uint32_t index, Parameter& parameter);
