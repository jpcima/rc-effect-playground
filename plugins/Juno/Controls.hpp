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
    //,{
    //    "Another preset",  // preset name
    //    {0.5f, ...}        // array of presetCount float param values
    //}
};

constexpr uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

void InitParameter(uint32_t index, Parameter& parameter);
