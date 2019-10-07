#include "Controls.hpp"

void InitParameter(uint32_t index, Parameter& parameter)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < paramCount,);

    parameter.hints = kParameterIsAutomable;

    switch (index) {
    case pIdBypass:
        parameter.initDesignation(kParameterDesignationBypass);
        break;
    case pIdLfoType:
        parameter.symbol = "lfo_type";
        parameter.name = "LFO type (0=triangle, 1=sine) (circuit characteristic)";
        parameter.ranges = ParameterRanges(0, 0, 1);
        parameter.hints |= kParameterIsInteger;
        break;
    case pIdLfoSpeed:
        parameter.symbol = "lfo_speed";
        parameter.name = "LFO speed (Hz) (circuit characteristic)";
        parameter.unit = "Hz";
        parameter.ranges = ParameterRanges(0.4, 0.1, 10.0);
        parameter.hints |= kParameterIsLogarithmic;
        break;
    case pIdLfoAmplitude:
        parameter.symbol = "lfo_amplitude";
        parameter.name = "LFO amplitude (circuit characteristic)";
        parameter.ranges = ParameterRanges(1.0, 0.0, 1.0);
        break;
    case pIdLineDelay:
        parameter.symbol = "line_delay";
        parameter.name = "Line Delay (ms) (circuit characteristic)";
        parameter.unit = "ms";
        parameter.ranges = ParameterRanges(10.0, 5.0, 50.0);
        break;
    case pIdDelayModAmount:
        parameter.symbol = "delay_mod_amount";
        parameter.name = u8"Delay Mod Amount (×) (circuit characteristic)";
        parameter.ranges = ParameterRanges(0.2, 0.05, 0.5);
        break;
    case pIdWet:
        parameter.symbol = "wet";
        parameter.name = "Wet (dB) (Mix adjust)";
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(-6.0, -60.0, 0.0);
        break;
    case pIdDry:
        parameter.symbol = "dry";
        parameter.name = "Dry (dB) (Mix adjust)";
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(-6.0, -60.0, 0.0);
        break;
    }
}
