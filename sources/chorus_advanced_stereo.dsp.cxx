/* ------------------------------------------------------------
name: "chorus_advanced_stereo"
Code generated with Faust 2.15.11 (https://faust.grame.fr)
Compilation options: -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faustChorusAdvancedStereoImpl_H__
#define  __faustChorusAdvancedStereoImpl_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <math.h>


class faustChorusAdvancedStereoImplSIG0 {
	
  private:
	
	int iRec8[2];
	
  public:
	
	int getNumInputsfaustChorusAdvancedStereoImplSIG0() {
		return 0;
		
	}
	int getNumOutputsfaustChorusAdvancedStereoImplSIG0() {
		return 1;
		
	}
	int getInputRatefaustChorusAdvancedStereoImplSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaustChorusAdvancedStereoImplSIG0(int channel) {
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
	
	void instanceInitfaustChorusAdvancedStereoImplSIG0(int samplingFreq) {
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec8[l8] = 0;
			
		}
		
	}
	
	void fillfaustChorusAdvancedStereoImplSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec8[0] = (iRec8[1] + 1);
			float fTemp10 = float((iRec8[0] + -1));
			float fTemp11 = (1.52587891e-05f * fTemp10);
			float fTemp12 = (6.10351562e-05f * fTemp10);
			output[i] = (0.5f * (((fTemp11 < 0.25f)?fTemp12:((fTemp11 < 0.75f)?(2.0f - fTemp12):(fTemp12 + -4.0f))) + 1.0f));
			iRec8[1] = iRec8[0];
			
		}
		
	}

};

faustChorusAdvancedStereoImplSIG0* newfaustChorusAdvancedStereoImplSIG0() { return (faustChorusAdvancedStereoImplSIG0*)new faustChorusAdvancedStereoImplSIG0(); }
void deletefaustChorusAdvancedStereoImplSIG0(faustChorusAdvancedStereoImplSIG0* dsp) { delete dsp; }


class faustChorusAdvancedStereoImplSIG1 {
	
  private:
	
	int iRec9[2];
	
  public:
	
	int getNumInputsfaustChorusAdvancedStereoImplSIG1() {
		return 0;
		
	}
	int getNumOutputsfaustChorusAdvancedStereoImplSIG1() {
		return 1;
		
	}
	int getInputRatefaustChorusAdvancedStereoImplSIG1(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaustChorusAdvancedStereoImplSIG1(int channel) {
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
	
	void instanceInitfaustChorusAdvancedStereoImplSIG1(int samplingFreq) {
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iRec9[l9] = 0;
			
		}
		
	}
	
	void fillfaustChorusAdvancedStereoImplSIG1(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec9[0] = (iRec9[1] + 1);
			output[i] = (0.5f * (std::sin((9.58738019e-05f * float((iRec9[0] + -1)))) + 1.0f));
			iRec9[1] = iRec9[0];
			
		}
		
	}

};

faustChorusAdvancedStereoImplSIG1* newfaustChorusAdvancedStereoImplSIG1() { return (faustChorusAdvancedStereoImplSIG1*)new faustChorusAdvancedStereoImplSIG1(); }
void deletefaustChorusAdvancedStereoImplSIG1(faustChorusAdvancedStereoImplSIG1* dsp) { delete dsp; }

static float ftbl0faustChorusAdvancedStereoImplSIG0[65536];
static float ftbl1faustChorusAdvancedStereoImplSIG1[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS faustChorusAdvancedStereoImpl
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faustChorusAdvancedStereoImpl : public faustObject {
	
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
	float fConst5;
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	FAUSTFLOAT fHslider5;
	float fRec7[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "chorus_advanced_stereo");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "chorus_advanced_stereo");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 2;
		
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
		faustChorusAdvancedStereoImplSIG0* sig0 = newfaustChorusAdvancedStereoImplSIG0();
		sig0->instanceInitfaustChorusAdvancedStereoImplSIG0(samplingFreq);
		sig0->fillfaustChorusAdvancedStereoImplSIG0(65536, ftbl0faustChorusAdvancedStereoImplSIG0);
		faustChorusAdvancedStereoImplSIG1* sig1 = newfaustChorusAdvancedStereoImplSIG1();
		sig1->instanceInitfaustChorusAdvancedStereoImplSIG1(samplingFreq);
		sig1->fillfaustChorusAdvancedStereoImplSIG1(65536, ftbl1faustChorusAdvancedStereoImplSIG1);
		deletefaustChorusAdvancedStereoImplSIG0(sig0);
		deletefaustChorusAdvancedStereoImplSIG1(sig1);
		
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
		fHslider4 = FAUSTFLOAT(180.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		
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
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
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
	
	virtual faustChorusAdvancedStereoImpl* clone() {
		return new faustChorusAdvancedStereoImpl();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("chorus_advanced_stereo");
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("LFO rate", &fHslider3, 0.5f, 0.100000001f, 20.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "3", "");
		ui_interface->addHorizontalSlider("LFO shape", &fHslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "4", "");
		ui_interface->declare(&fHslider4, "unit", "deg");
		ui_interface->addHorizontalSlider("LFO phase", &fHslider4, 180.0f, 0.0f, 360.0f, 1.0f);
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
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst2 * float(fCheckbox0));
		float fSlow1 = (fConst2 * std::pow(10.0f, (0.0500000007f * float(fHslider0))));
		float fSlow2 = (fConst3 * float(fHslider1));
		float fSlow3 = (fConst3 * float(fHslider2));
		float fSlow4 = (fConst2 * float(fHslider3));
		float fSlow5 = (fConst5 * float(fHslider4));
		float fSlow6 = (fConst2 * float(fHslider5));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (fConst1 * fRec0[1]));
			float fTemp0 = (1.0f - fRec0[0]);
			float fTemp1 = float(input0[i]);
			float fTemp2 = float(input1[i]);
			float fTemp3 = (fTemp1 + fTemp2);
			float fTemp4 = (0.586793125f * fTemp3);
			fRec1[0] = (fSlow1 + (fConst1 * fRec1[1]));
			fRec2[0] = (fSlow2 + (fConst1 * fRec2[1]));
			fRec3[0] = (fSlow3 + (fConst1 * fRec3[1]));
			float fTemp5 = (fRec3[0] - fRec2[0]);
			fRec5[0] = (fSlow4 + (fConst1 * fRec5[1]));
			float fTemp6 = (fRec4[1] + (fConst4 * fRec5[0]));
			fRec4[0] = (fTemp6 - float(int(fTemp6)));
			fRec6[0] = (fSlow5 + (fConst1 * fRec6[1]));
			float fTemp7 = (fRec4[0] + fRec6[0]);
			float fTemp8 = (fTemp7 - float(int(fTemp7)));
			fRec7[0] = (fSlow6 + (fConst1 * fRec7[1]));
			float fTemp9 = (1.0f - fRec7[0]);
			int iTemp13 = (int((65536.0f * fTemp8)) % 65536);
			float fTemp14 = ftbl0faustChorusAdvancedStereoImplSIG0[iTemp13];
			float fTemp15 = ftbl1faustChorusAdvancedStereoImplSIG1[iTemp13];
			float fTemp16 = std::min<float>(1.0f, (2.0f * fRec7[0]));
			float fTemp17 = (1.0f - fTemp16);
			int iTemp18 = (int((65536.0f * fRec4[0])) % 65536);
			float fTemp19 = ftbl0faustChorusAdvancedStereoImplSIG0[iTemp18];
			float fTemp20 = ftbl1faustChorusAdvancedStereoImplSIG1[iTemp18];
			float fTemp21 = float(AnalogDelay3(float((fRec2[0] + (fTemp5 * ((fRec4[0] < 0.5f)?((fTemp17 * fTemp19) + (fTemp16 * fTemp20)):((fTemp9 * fTemp19) + (fRec7[0] * fTemp20)))))), float((0.707106769f * fTemp3))));
			output0[i] = FAUSTFLOAT(((0.707106769f * (fTemp0 * (fTemp4 + ((0.829850793f * fTemp1) + (fRec1[0] * (float(AnalogDelay1(float((fRec2[0] + (fTemp5 * ((fTemp8 < 0.5f)?((fTemp17 * fTemp14) + (fTemp16 * fTemp15)):((fTemp9 * fTemp14) + (fRec7[0] * fTemp15)))))), float(fTemp1))) + fTemp21)))))) + (fRec0[0] * fTemp1)));
			float fTemp22 = (fRec4[0] + (1.0f - (fRec6[0] + float(int((fRec4[0] + (1.0f - fRec6[0])))))));
			int iTemp23 = (int((65536.0f * fTemp22)) % 65536);
			float fTemp24 = ftbl0faustChorusAdvancedStereoImplSIG0[iTemp23];
			float fTemp25 = ftbl1faustChorusAdvancedStereoImplSIG1[iTemp23];
			output1[i] = FAUSTFLOAT(((0.707106769f * (fTemp0 * ((0.829850793f * fTemp2) + (fTemp4 + (fRec1[0] * (fTemp21 + float(AnalogDelay2(float((fRec2[0] + (fTemp5 * ((fTemp22 < 0.5f)?((fTemp17 * fTemp24) + (fTemp16 * fTemp25)):((fTemp9 * fTemp24) + (fRec7[0] * fTemp25)))))), float(fTemp2))))))))) + (fRec0[0] * fTemp2)));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}

};

#endif
