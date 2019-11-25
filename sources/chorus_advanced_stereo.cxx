//
// Wrapper of Faust chorus to hack the C++ analog delay
// into the processing function.
//

#include "faust_object.h"
#include "bbd_line.h"
#include "bbd_filter.h"
#include <cassert>

///
struct faustChorusAdvancedStereoExtra {
    enum { NumStages = 256 };
    BBD_Line fLine1;
    BBD_Line fLine2;
    BBD_Line fLine3;
};

/// Foreign `ffunction` macros invoked from Faust code
#define AnalogDelay1(d, x) (getChorusExtra(*this).fLine1.process_single(x, BBD_Line::hz_rate_for_delay(d, faustChorusAdvancedStereoExtra::NumStages) * (1.0f/fSamplingFreq)))
#define AnalogDelay2(d, x) (getChorusExtra(*this).fLine2.process_single(x, BBD_Line::hz_rate_for_delay(d, faustChorusAdvancedStereoExtra::NumStages) * (1.0f/fSamplingFreq)))
#define AnalogDelay3(d, x) (getChorusExtra(*this).fLine3.process_single(x, BBD_Line::hz_rate_for_delay(d, faustChorusAdvancedStereoExtra::NumStages) * (1.0f/fSamplingFreq)))
class faustChorusAdvancedStereoImpl;
static faustChorusAdvancedStereoExtra &getChorusExtra(faustChorusAdvancedStereoImpl &c);
///


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "chorus_advanced_stereo.dsp.cxx"

#pragma GCC diagnostic pop

///
class faustChorusAdvancedStereo final : public faustChorusAdvancedStereoImpl, public faustObject::UI {
public:
    faustChorusAdvancedStereo()
    {
        classInit(44100);
        instanceConstants(44100);
        instanceResetUserInterface();
        instanceClear();

        buildUserInterface(this);

        assert(fControlBypass);
        assert(fControlLfoRate);
        assert(fControlLfoShape);
        assert(fControlLfoPhase);
        assert(fControlDelayDomain1);
        assert(fControlDelayDomain2);
        assert(fControlPresence);
    }

    void instanceConstants(int samplingFreq) override
    {
        faustChorusAdvancedStereoImpl::instanceConstants(samplingFreq);
        fExtra.fLine1.setup(samplingFreq, faustChorusAdvancedStereoExtra::NumStages, bbd_fin_j60, bbd_fout_j60);
        fExtra.fLine2.setup(samplingFreq, faustChorusAdvancedStereoExtra::NumStages, bbd_fin_j60, bbd_fout_j60);
        fExtra.fLine3.setup(samplingFreq, faustChorusAdvancedStereoExtra::NumStages, bbd_fin_j60, bbd_fout_j60);
    }

    void instanceClear() override
    {
        faustChorusAdvancedStereoImpl::instanceClear();
        fExtra.fLine1.clear();
        fExtra.fLine2.clear();
        fExtra.fLine3.clear();
    }

    /* Find control ports (by they number property, eg. "[1]") */
    void declare(float *control, const char *property, const char *value) override
    {
        switch (atoi(property)) {
        case 1:
            fControlBypass = control;
            break;
        case 2:
            fControlLfoRate = control;
            break;
        case 3:
            fControlLfoShape = control;
            break;
        case 4:
            fControlLfoPhase = control;
            break;
        case 5:
            fControlDelayDomain1 = control;
            break;
        case 6:
            fControlDelayDomain2 = control;
            break;
        case 7:
            fControlPresence = control;
            break;
        }
        (void)value;
    }

    float *fControlBypass = nullptr;
    float *fControlLfoRate = nullptr;
    float *fControlLfoShape = nullptr;
    float *fControlLfoPhase = nullptr;
    float *fControlDelayDomain1 = nullptr;
    float *fControlDelayDomain2 = nullptr;
    float *fControlPresence = nullptr;

    faustChorusAdvancedStereoExtra fExtra;
};

///
static faustChorusAdvancedStereoExtra &getChorusExtra(faustChorusAdvancedStereoImpl &c)
{
    return static_cast<faustChorusAdvancedStereo &>(c).fExtra;
}
