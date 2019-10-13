//
// Wrapper of Faust chorus to hack the C++ analog delay
// into the processing function.
//

#include "faust_object.h"
#include "bbd_line.h"
#include "bbd_filter.h"
#include <cassert>

///
struct faustChorusExtra {
    enum { NumStages = 256 };
    BBD_Line fLine1;
    BBD_Line fLine2;
};

/// Foreign `ffunction` macros invoked from Faust code
#define AnalogDelay1(d, x) (getChorusExtra(*this).fLine1.process_single(x, BBD_Line::hz_rate_for_delay(d, faustChorusExtra::NumStages) * (1.0f/fSamplingFreq)))
#define AnalogDelay2(d, x) (getChorusExtra(*this).fLine2.process_single(x, BBD_Line::hz_rate_for_delay(d, faustChorusExtra::NumStages) * (1.0f/fSamplingFreq)))
class faustChorusImpl;
static faustChorusExtra &getChorusExtra(faustChorusImpl &c);
///


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "chorus.dsp.cxx"

#pragma GCC diagnostic pop

///
class faustChorus final : public faustChorusImpl, public faustObject::UI {
public:
    faustChorus()
    {
        instanceConstants(44100);
        instanceResetUserInterface();
        instanceClear();

        buildUserInterface(this);

        assert(fControlChorusI);
        assert(fControlChorusII);
    }

    void instanceConstants(int samplingFreq) override
    {
        faustChorusImpl::instanceConstants(samplingFreq);
        fExtra.fLine1.setup(samplingFreq, faustChorusExtra::NumStages, bbd_fin_j60, bbd_fout_j60);
        fExtra.fLine2.setup(samplingFreq, faustChorusExtra::NumStages, bbd_fin_j60, bbd_fout_j60);
    }

    void instanceClear() override
    {
        faustChorusImpl::instanceClear();
        fExtra.fLine1.clear();
        fExtra.fLine2.clear();
    }

    /* Find control ports (by they number property, eg. "[1]") */
    void declare(float *control, const char *property, const char *value) override
    {
        switch (atoi(property)) {
        case 1:
            fControlChorusI = control;
            break;
        case 2:
            fControlChorusII = control;
            break;
        }
        (void)value;
    }

    float *fControlChorusI = nullptr;
    float *fControlChorusII = nullptr;

    faustChorusExtra fExtra;
};

///
static faustChorusExtra &getChorusExtra(faustChorusImpl &c)
{
    return static_cast<faustChorus &>(c).fExtra;
}
