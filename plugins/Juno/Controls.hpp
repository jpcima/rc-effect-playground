#pragma once
#include "DistrhoPlugin.hpp"


enum LfoType {
    lfoTriangle,
    lfoSine,
    lfoTypeCount
};

enum Parameters {
    pIdBypass,
    pIdLfoType,
    pIdLfoSpeed,
    pIdLfoAmplitude,
    pIdFast,
    pIdLineDelay,
    pIdDelayModAmount,
    pIdWet,
    pIdDry,
    paramCount
};

enum States {
    stateCount
};

struct Preset {
    const char* name;
    float params[paramCount];
};

const Preset factoryPresets[] = {
    {
        "JX-3P", {
            1.0f,           // lv2_enabled
            lfoTriangle,    // lfo_type
            0.25f,          // lfo_speed
            0.75f,          // lfo_amplitude
            0.0f,           // fast
            12.0f,          // line_delay
            0.5f,           // delay_mod_amount
            -3.0f,          // wet
            -3.0f           // dry
        }
    }
    //,{
    //    "Another preset",  // preset name
    //    {0.5f, ...}        // array of presetCount float param values
    //}
};

constexpr uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

void InitParameter(uint32_t index, Parameter& parameter);
