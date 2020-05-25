#include "Controls.hpp"

void InitParameter(uint32_t index, Parameter& parameter)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < paramCount,);

    parameter.hints = kParameterIsAutomable;

    switch (index) {
    case paramTypeI:
        parameter.symbol = "type_1";
        parameter.name = "Chorus (I)";
        parameter.hints |= kParameterIsBoolean|kParameterIsInteger;
        break;
    case paramTypeII:
        parameter.symbol = "type_2";
        parameter.name = "Chorus (II)";
        parameter.hints |= kParameterIsBoolean|kParameterIsInteger;
        break;
    }
}
