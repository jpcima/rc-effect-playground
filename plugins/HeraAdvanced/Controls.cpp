#include "Controls.hpp"

void InitParameter(uint32_t index, Parameter& parameter)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < paramCount,);

    parameter.hints = kParameterIsAutomable;

    switch (index) {
    case pIdBypass:
        parameter.initDesignation(kParameterDesignationBypass);
        break;
    case pIdLfoRate:
        parameter.symbol = "lfo_rate";
        parameter.name = "LFO rate";
        parameter.unit = "Hz";
        parameter.hints |= kParameterIsLogarithmic;
        parameter.ranges = ParameterRanges(0.5, 0.1, 20.);
        break;
    case pIdLfoShape:
        parameter.symbol = "lfo_shape";
        parameter.name = "LFO shape";
        parameter.ranges = ParameterRanges(0., 0., 1.);
        break;
    case pIdLfoPhase:
        parameter.symbol = "lfo_phase";
        parameter.name = "LFO phase";
        parameter.unit = "deg";
        parameter.ranges = ParameterRanges(180., 0., 360.);
        break;
    case pIdDelayDomain1:
        parameter.symbol = "delay_domain1";
        parameter.name = "Delay domain 1";
        parameter.unit = "ms";
        parameter.ranges = ParameterRanges(1.54, 0.5, 10.);
        break;
    case pIdDelayDomain2:
        parameter.symbol = "delay_domain2";
        parameter.name = "Delay domain 2";
        parameter.unit = "ms";
        parameter.ranges = ParameterRanges(5.15, 0.5, 10.);
        break;
    case pIdPresence:
        parameter.symbol = "presence";
        parameter.name = "Presence";
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0., -10., 10.);
        break;
    }
}
