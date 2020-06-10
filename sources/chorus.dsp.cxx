/* ------------------------------------------------------------
name: "chorus"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faustChorusImpl_H__
#define  __faustChorusImpl_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <math.h>

class faustChorusImplSIG0 {
	
  private:
	
	int iRec6[2];
	
  public:
	
	int getNumInputsfaustChorusImplSIG0() {
		return 0;
	}
	int getNumOutputsfaustChorusImplSIG0() {
		return 1;
	}
	int getInputRatefaustChorusImplSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRatefaustChorusImplSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitfaustChorusImplSIG0(int sample_rate) {
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec6[l6] = 0;
		}
	}
	
	void fillfaustChorusImplSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec6[0] = (iRec6[1] + 1);
			table[i] = std::sin((9.58738019e-05f * float((iRec6[0] + -1))));
			iRec6[1] = iRec6[0];
		}
	}

};

static faustChorusImplSIG0* newfaustChorusImplSIG0() { return (faustChorusImplSIG0*)new faustChorusImplSIG0(); }
static void deletefaustChorusImplSIG0(faustChorusImplSIG0* dsp) { delete dsp; }

static float ftbl0faustChorusImplSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS faustChorusImpl
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faustChorusImpl : public faustObject {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fConst3;
	float fRec5[2];
	float fRec4[2];
	float fRec7[2];
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "chorus.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "chorus");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
		faustChorusImplSIG0* sig0 = newfaustChorusImplSIG0();
		sig0->instanceInitfaustChorusImplSIG0(sample_rate);
		sig0->fillfaustChorusImplSIG0(65536, ftbl0faustChorusImplSIG0);
		deletefaustChorusImplSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = std::exp((0.0f - (10.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = (1.0f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual faustChorusImpl* clone() {
		return new faustChorusImpl();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("chorus");
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->addCheckButton("Chorus (I)", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "2", "");
		ui_interface->addCheckButton("Chorus (II)", &fCheckbox1);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = ((float(fCheckbox0) != 0.0f) | ((float(fCheckbox1) != 0.0f) << 1));
		float fSlow1 = (fConst2 * float((iSlow0 != 0)));
		int iSlow2 = (iSlow0 + -1);
		int iSlow3 = (iSlow2 >= 2);
		float fSlow4 = (fConst2 * (iSlow3 ? 0.00322000007f : 0.00153999997f));
		float fSlow5 = (fConst2 * (iSlow3 ? 0.0035600001f : 0.0051500001f));
		float fSlow6 = (fConst2 * float((iSlow3 ? 1 : 0)));
		float fSlow7 = (fConst2 * (iSlow3 ? 9.75f : ((iSlow2 >= 1) ? 0.862999976f : 0.513000011f)));
		float fSlow8 = (fConst2 * (iSlow3 ? 0.00328000006f : 0.00150999997f));
		float fSlow9 = (fConst2 * (iSlow3 ? 0.00365000009f : 0.00540000014f));
		float fSlow10 = (fConst2 * float((iSlow3 ? 0 : 1)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec0[0] = (fSlow1 + (fConst1 * fRec0[1]));
			float fTemp1 = (fTemp0 * (1.0f - fRec0[0]));
			float fTemp2 = (0.829999983f * fTemp0);
			fRec1[0] = ((fConst1 * fRec1[1]) + fSlow4);
			fRec2[0] = ((fConst1 * fRec2[1]) + fSlow5);
			fRec3[0] = ((fConst1 * fRec3[1]) + fSlow6);
			fRec5[0] = ((fConst1 * fRec5[1]) + fSlow7);
			float fTemp3 = (fRec4[1] + (fConst3 * fRec5[1]));
			fRec4[0] = (fTemp3 - std::floor(fTemp3));
			float fTemp4 = (fRec7[1] + (fConst3 * fRec5[0]));
			fRec7[0] = (fTemp4 - std::floor(fTemp4));
			float fTemp5 = (((1.0f - fRec3[0]) * (1.0f - std::fabs(((2.0f * fRec4[0]) + -1.0f)))) + (0.5f * (fRec3[0] * (ftbl0faustChorusImplSIG0[int((65536.0f * fRec7[0]))] + 1.0f))));
			output0[i] = FAUSTFLOAT((fTemp1 + (fRec0[0] * (fTemp2 + float(AnalogDelay1(float((fRec1[0] + ((fRec2[0] - fRec1[0]) * fTemp5))), float(fTemp0)))))));
			fRec8[0] = ((fConst1 * fRec8[1]) + fSlow8);
			fRec9[0] = ((fConst1 * fRec9[1]) + fSlow9);
			fRec10[0] = ((fConst1 * fRec10[1]) + fSlow10);
			output1[i] = FAUSTFLOAT((fTemp1 + (fRec0[0] * (fTemp2 + float(AnalogDelay2(float((fRec8[0] + ((fRec9[0] - fRec8[0]) * (((1.0f - fRec10[0]) * fTemp5) + (fRec10[0] * (1.0f - fTemp5)))))), float(fTemp0)))))));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
		}
	}

};

#endif
