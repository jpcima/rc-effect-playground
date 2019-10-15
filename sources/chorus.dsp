import("stdfaust.lib");

buttonI = checkbox("[1] Chorus (I)") : !=(0);
buttonII = checkbox("[2] Chorus (II)") : !=(0);

process = chorus with {
  /* Mode: 0=Off 1=(I), 2=(II), 3=(I + II) */
  mode = buttonI | (buttonII << 1);
  enabled = mode != 0;
  selectByMode = ba.selectn(3, mode-1);

  /* (I) */
  I = environment {
    lfoRate = 0.513;
    lfoShape = 0; /* triangle */
    delaymin = 1.54e-3;
    delaymax = 5.15e-3;
    stereo = 1;
  };

  /* (II) */
  II = environment {
    lfoRate = 0.863;
    lfoShape = 0; /* triangle */
    delaymin = 1.54e-3;
    delaymax = 5.15e-3;
    stereo = 1;
  };

  /* (I + II) */
  III = environment {
    lfoRate = 9.75; /* by ear and experiment */
    // found in documents and not matching the Juno60 sample:
    // 15.175 Hz (too fast), 8 Hz (too slow)
    lfoShape = 1; /* sine-like */
    delaymin = 3.22e-3;
    delaymax = 3.56e-3;
    stereo = 0;
  };

  /**/
  s = environment {
    lfoRate = (I.lfoRate, II.lfoRate, III.lfoRate) : selectByMode : smooth;
    lfoShape = (I.lfoShape, II.lfoShape, III.lfoShape) : selectByMode : smooth;
    delaymin = (I.delaymin, II.delaymin, III.delaymin) : selectByMode : smooth;
    delaymax = (I.delaymax, II.delaymax, III.delaymax) : selectByMode : smooth;
    stereo = (I.stereo, II.stereo, III.stereo) : selectByMode : smooth;
  };

  /**/
  chorus(x) =
    ((x, out1) : si.interpolate(enabled : smooth)),
    ((x, out2) : si.interpolate(enabled : smooth))
  with {
    out1 = x <: (*(0.83), delayModel.line1(lfo1 : delayAt)) :> +;
    out2 = x <: (*(0.83), delayModel.line2(lfo2 : delayAt)) :> +;

    /* Delay model */
    delayModel = analogDelayModel;
    //delayModel = digitalDelayModel;

    /* Capacity of delay */
    delaycap = 10e-3; // seconds, must be >> delay time
    delaycapframes = int(ceil(delaycap * ma.SR)); // frames, rounded up

    /* LFO */
    rawLfo = (triangle, sine) : si.interpolate(s.lfoShape) with {
      triangle = os.lf_trianglepos(s.lfoRate);
      sine = os.osc(s.lfoRate) : +(1.) : *(0.5);
    };
    rawInverseLfo = 1. - rawLfo;
    lfo1 = rawLfo;
    lfo2 = (rawLfo, rawInverseLfo) : si.interpolate(s.stereo);

    /* Filter */
    delayLPF = fi.lowpass(4, 10000.); // a simulation of BBD antialising LPF at input and output

    /* Delay */
    digitalDelayModel = environment {
      line1(d) = delayLPF : de.fdelay(delaycapframes, d*ma.SR) : delayLPF;
      line2(d) = line1(d);
    };
    analogDelayModel = environment {
      /* external functions call the BBD which is implemented in C++ code */
      line1 = ffunction(float AnalogDelay1(float, float), <math.h>, "");
      line2 = ffunction(float AnalogDelay2(float, float), <math.h>, "");
    };
    delayAt = *(s.delaymax - s.delaymin) : +(s.delaymin);
  };

  /**/
  smooth = si.smooth(ba.tau2pole(100e-3));
};
