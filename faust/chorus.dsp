import("stdfaust.lib");

bypass = checkbox("[1] Bypass");
gain1 = hslider("[2] Line 1 gain", 0.0, -20.0, 0.0, 1.0) : ba.db2linear : si.smoo;
gain2 = hslider("[3] Line 2 gain", 0.0, -20.0, 0.0, 1.0) : ba.db2linear : si.smoo;
speed = checkbox("[4] Speed");

process(x) =
  ba.if(bypass, x, (x + gain1 * (x : line1) + gain2 * (x : line2))),
  ba.if(bypass, x, (x + gain1 * (x : line2) + gain2 * (x : line1)))
with {
  lfoRate = ba.if(speed, lfoRateI, lfoRateII);

  lfo1 = 0.5 * os.lf_triangle(lfoRate);
  lfo2 = 1. - lfo1;

  delayfilter = fi.lowpass(5, 10000.); // a simulation of BBD antialising LPF at input and output

  line1 = delayfilter : de.fdelay(delaycapframes, lfo1 : delayAt : *(ma.SR)) : delayfilter;
  line2 = delayfilter : de.fdelay(delaycapframes, lfo2 : delayAt : *(ma.SR)) : delayfilter;
  // line1 = delayfilter : de.fdelay1(delaycapframes, lfo1 : delayAt : *(ma.SR)) : delayfilter;
  // line2 = delayfilter : de.fdelay1(delaycapframes, lfo2 : delayAt : *(ma.SR)) : delayfilter;

  delayAt = *(delaymax - delaymin) : +(delaymin);

  lfoRateI = 0.95;
  lfoRateII = 1.6;

  delaycap = 10e-3; // delay capacity, must be >> delay time
  delaycapframes = int(ceil(delaycap * ma.SR)); // the same in frames, rounded up

  delaymin = 1.5e-3;
  delaymax = 3.5e-3;
};
