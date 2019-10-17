/* ------------------------------------------------------------
name: "chorus_advanced"
Code generated with Faust 2.15.11 (https://faust.grame.fr)
Compilation options: -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faustChorusAdvancedImpl_H__
#define  __faustChorusAdvancedImpl_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <math.h>


class faustChorusAdvancedImplSIG0 {
	
  private:
	
	int iRec7[2];
	
  public:
	
	int getNumInputsfaustChorusAdvancedImplSIG0() {
		return 0;
		
	}
	int getNumOutputsfaustChorusAdvancedImplSIG0() {
		return 1;
		
	}
	int getInputRatefaustChorusAdvancedImplSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaustChorusAdvancedImplSIG0(int channel) {
		int rate;
		switch (channel) {
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
	
	void instanceInitfaustChorusAdvancedImplSIG0(int samplingFreq) {
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iRec7[l7] = 0;
			
		}
		
	}
	
	void fillfaustChorusAdvancedImplSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec7[0] = (iRec7[1] + 1);
			float fTemp6 = float((iRec7[0] + -1));
			float fTemp7 = (1.52587891e-05f * fTemp6);
			float fTemp8 = (6.10351562e-05f * fTemp6);
			output[i] = (0.5f * (((fTemp7 < 0.25f)?fTemp8:((fTemp7 < 0.75f)?(2.0f - fTemp8):(fTemp8 + -4.0f))) + 1.0f));
			iRec7[1] = iRec7[0];
			
		}
		
	}

};

faustChorusAdvancedImplSIG0* newfaustChorusAdvancedImplSIG0() { return (faustChorusAdvancedImplSIG0*)new faustChorusAdvancedImplSIG0(); }
void deletefaustChorusAdvancedImplSIG0(faustChorusAdvancedImplSIG0* dsp) { delete dsp; }


class faustChorusAdvancedImplSIG1 {
	
  private:
	
	int iRec8[2];
	
  public:
	
	int getNumInputsfaustChorusAdvancedImplSIG1() {
		return 0;
		
	}
	int getNumOutputsfaustChorusAdvancedImplSIG1() {
		return 1;
		
	}
	int getInputRatefaustChorusAdvancedImplSIG1(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaustChorusAdvancedImplSIG1(int channel) {
		int rate;
		switch (channel) {
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
	
	void instanceInitfaustChorusAdvancedImplSIG1(int samplingFreq) {
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec8[l8] = 0;
			
		}
		
	}
	
	void fillfaustChorusAdvancedImplSIG1(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec8[0] = (iRec8[1] + 1);
			output[i] = (0.5f * (std::sin((9.58738019e-05f * float((iRec8[0] + -1)))) + 1.0f));
			iRec8[1] = iRec8[0];
			
		}
		
	}

};

faustChorusAdvancedImplSIG1* newfaustChorusAdvancedImplSIG1() { return (faustChorusAdvancedImplSIG1*)new faustChorusAdvancedImplSIG1(); }
void deletefaustChorusAdvancedImplSIG1(faustChorusAdvancedImplSIG1* dsp) { delete dsp; }

static float ftbl0faustChorusAdvancedImplSIG0[65536];
static float ftbl1faustChorusAdvancedImplSIG1[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS faustChorusAdvancedImpl
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faustChorusAdvancedImpl : public faustObject {
	
 private:
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fCheckbox0;
	float fRec0[2];
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fRec4[2];
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	float fConst5;
	FAUSTFLOAT fHslider5;
	float fRec9[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "chorus_advanced");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "chorus_advanced");
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
		switch (channel) {
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
		switch (channel) {
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
	
	static void classInit(int samplingFreq) {
		faustChorusAdvancedImplSIG0* sig0 = newfaustChorusAdvancedImplSIG0();
		sig0->instanceInitfaustChorusAdvancedImplSIG0(samplingFreq);
		sig0->fillfaustChorusAdvancedImplSIG0(65536, ftbl0faustChorusAdvancedImplSIG0);
		faustChorusAdvancedImplSIG1* sig1 = newfaustChorusAdvancedImplSIG1();
		sig1->instanceInitfaustChorusAdvancedImplSIG1(samplingFreq);
		sig1->fillfaustChorusAdvancedImplSIG1(65536, ftbl1faustChorusAdvancedImplSIG1);
		deletefaustChorusAdvancedImplSIG0(sig0);
		deletefaustChorusAdvancedImplSIG1(sig1);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = std::exp((0.0f - (10.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = (0.00100000005f * fConst2);
		fConst4 = (1.0f / fConst0);
		fConst5 = (0.00277777785f * fConst2);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(1.54f);
		fHslider2 = FAUSTFLOAT(5.1500000000000004f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(180.0f);
		
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
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual faustChorusAdvancedImpl* clone() {
		return new faustChorusAdvancedImpl();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("chorus_advanced");
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("LFO rate", &fHslider3, 0.5f, 0.100000001f, 20.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->addHorizontalSlider("LFO shape", &fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "4", "");
		ui_interface->declare(&fHslider5, "unit", "deg");
		ui_interface->addHorizontalSlider("LFO phase", &fHslider5, 180.0f, 0.0f, 360.0f, 1.0f);
		ui_interface->declare(&fHslider1, "5", "");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay domain 1", &fHslider1, 1.53999996f, 0.5f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "6", "");
		ui_interface->declare(&fHslider2, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay domain 2", &fHslider2, 5.1500001f, 0.5f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "7", "");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Presence", &fHslider0, 0.0f, -10.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst2 * float(fCheckbox0));
		float fSlow1 = (fConst2 * std::pow(10.0f, (0.0500000007f * float(fHslider0))));
		float fSlow2 = (fConst3 * float(fHslider1));
		float fSlow3 = (fConst3 * float(fHslider2));
		float fSlow4 = (fConst2 * float(fHslider3));
		float fSlow5 = (fConst2 * float(fHslider4));
		float fSlow6 = (fConst5 * float(fHslider5));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (fConst1 * fRec0[1]));
			float fTemp0 = (1.0f - fRec0[0]);
			float fTemp1 = float(input0[i]);
			float fTemp2 = (0.829850793f * fTemp1);
			fRec1[0] = (fSlow1 + (fConst1 * fRec1[1]));
			fRec2[0] = (fSlow2 + (fConst1 * fRec2[1]));
			fRec3[0] = (fSlow3 + (fConst1 * fRec3[1]));
			float fTemp3 = (fRec3[0] - fRec2[0]);
			fRec5[0] = (fSlow4 + (fConst1 * fRec5[1]));
			float fTemp4 = (fRec4[1] + (fConst4 * fRec5[0]));
			fRec4[0] = (fTemp4 - float(int(fTemp4)));
			fRec6[0] = (fSlow5 + (fConst1 * fRec6[1]));
			float fTemp5 = (1.0f - fRec6[0]);
			int iTemp9 = (int((65536.0f * fRec4[0])) % 65536);
			float fTemp10 = ftbl0faustChorusAdvancedImplSIG0[iTemp9];
			float fTemp11 = ftbl1faustChorusAdvancedImplSIG1[iTemp9];
			float fTemp12 = std::min<float>(1.0f, (2.0f * fRec6[0]));
			float fTemp13 = (1.0f - fTemp12);
			float fTemp14 = (fRec0[0] * fTemp1);
			output0[i] = FAUSTFLOAT(((fTemp0 * (fTemp2 + (fRec1[0] * float(AnalogDelay1(float((fRec2[0] + (fTemp3 * ((fRec4[0] < 0.5f)?((fTemp13 * fTemp10) + (fTemp12 * fTemp11)):((fTemp5 * fTemp10) + (fRec6[0] * fTemp11)))))), float(fTemp1)))))) + fTemp14));
			fRec9[0] = (fSlow6 + (fConst1 * fRec9[1]));
			float fTemp15 = (fRec4[0] + fRec9[0]);
			float fTemp16 = (fTemp15 - float(int(fTemp15)));
			int iTemp17 = (int((65536.0f * fTemp16)) % 65536);
			float fTemp18 = ftbl0faustChorusAdvancedImplSIG0[iTemp17];
			float fTemp19 = ftbl1faustChorusAdvancedImplSIG1[iTemp17];
			output1[i] = FAUSTFLOAT((fTemp14 + (fTemp0 * (fTemp2 + (fRec1[0] * float(AnalogDelay2(float((fRec2[0] + (fTemp3 * ((fTemp16 < 0.5f)?((fTemp13 * fTemp18) + (fTemp12 * fTemp19)):((fTemp5 * fTemp18) + (fRec6[0] * fTemp19)))))), float(fTemp1))))))));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec9[1] = fRec9[0];
			
		}
		
	}

};

#endif
