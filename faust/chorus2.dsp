import("stdfaust.lib");

bypass = checkbox("[1] Bypass");
speed = checkbox("[2] Speed");

process(x) =
  ba.if(bypass, x, (x + (x : line1))),
  ba.if(bypass, x, (x + (x : line2)))
with {
  lfoRate = ba.if(speed, lfoRateII, lfoRateI);

  lfo1 = os.lf_trianglepos(lfoRate);
  lfo2 = 1. - lfo1;

  delayfilter = fi.lowpass(4, 10000.); // a simulation of BBD antialising LPF at input and output

  line1 = delayfilter : de.fdelay(delaycapframes, lfo1 : delayAt : *(ma.SR)) : delayfilter;
  line2 = delayfilter : de.fdelay(delaycapframes, lfo2 : delayAt : *(ma.SR)) : delayfilter;

  delayAt = *(delaymax - delaymin) : +(delaymin);

  lfoRateI = 0.513;
  lfoRateII = 0.863;

  delaycap = 10e-3; // delay capacity, must be >> delay time
  delaycapframes = int(ceil(delaycap * ma.SR)); // the same in frames, rounded up

  //// correct
  delaymin = 1.66e-3;
  delaymax = 5.35e-3;
};
