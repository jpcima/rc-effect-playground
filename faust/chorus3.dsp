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
    delaymin = 1.66e-3;
    delaymax = 5.35e-3;
    stereo = 1;
  };

  /* (II) */
  II = environment {
    lfoRate = 0.863;
    lfoShape = 0; /* triangle */
    delaymin = 1.66e-3;
    delaymax = 5.35e-3;
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
    amount = (I.amount, II.amount, III.amount) : selectByMode : smooth;
  };

  /**/
  chorus(x) =
    ba.if(enabled, mixAttenuation * (x + (x : line(lfo1))), x),
    ba.if(enabled, mixAttenuation * (x + (x : line(lfo2))), x)
  with {
    mixAttenuation = 1./sqrt(2.);

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
    lfo2 = s.stereo * rawInverseLfo + (1. - s.stereo) * rawLfo;

    /* Filter */
    delayLPF = fi.lowpass(4, 10000.); // a simulation of BBD antialising LPF at input and output

    /* Delay */
    line(lfo) = delayLPF : de.fdelay(delaycapframes, lfo : delayAt : *(ma.SR)) : delayLPF with {
      delayAt = *(s.delaymax - s.delaymin) : +(s.delaymin);
    };
  };

  /**/
  smooth = si.smooth(ba.tau2pole(100e-3));
};
