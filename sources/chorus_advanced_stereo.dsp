import("stdfaust.lib");

bypass = checkbox("[1] Bypass");
lfoRate = hslider("[2] LFO rate [unit:Hz] [scale:log]", 0.5, 0.1, 20., 0.01) : smooth;
lfoShape = hslider("[3] LFO shape", 0., 0., 1., 0.01) : smooth;
lfoPhase = hslider("[4] LFO phase [unit:deg]", 180., 0., 360., 1.) : /(360.) : smooth;
delayMin = hslider("[5] Delay domain 1 [unit:ms]", 1.54, 0.5, 10, 0.01) : *(1e-3) : smooth;
delayMax = hslider("[6] Delay domain 2 [unit:ms]", 5.15, 0.5, 10, 0.01) : *(1e-3) : smooth;
directGain = ba.db2linear(-1.62);
effectGain = hslider("[7] Presence [unit:dB]", 0., -10., 10., 0.1) : ba.db2linear : smooth;

process(xLeft, xRight) =
  par(n, 2, ((out(n), in(n)) : si.interpolate(bypass : smooth)))
with {
  in(0/*LEFT*/) = xLeft;
  in(1/*RIGHT*/) = xRight;

  out(n) = (lineMono(n) + lineCrossover) : stereoDownMix;

  lineMono(n) = in(n) : lineMixed(n);
  lineCrossover = (xLeft + xRight) : stereoDownMix : lineMixed(2/*CROSS*/);
  lineMixed(n) = _ <: (_, lineModulated(n)) : mix;

  mix = (*(directGain), *(effectGain)) :> +;
  stereoDownMix = *(1./sqrt(2.)); /* maybe make it parameter */

  /* LFO */
  lfoPosition(0/*LEFT*/) = wrap(lfoPosition(2/*CROSS*/) + lfoPhase);
  lfoPosition(1/*RIGHT*/) = wrap(lfoPosition(2/*CROSS*/) + 1. - lfoPhase);
  lfoPosition(2/*CROSS*/) = phasor01(lfoRate);
  lfo(n) = lfoWave(lfoShape, lfoPosition(n));

  /* Delay */
  line(0/*LEFT*/) = ffunction(float AnalogDelay1(float, float), <math.h>, "");
  line(1/*RIGHT*/) = ffunction(float AnalogDelay2(float, float), <math.h>, "");
  line(2/*CROSS*/) = ffunction(float AnalogDelay3(float, float), <math.h>, "");
  lineModulated(n) = line(n, lfo(n) : delayAt);

  delayAt = *(delayMax - delayMin) : +(delayMin);
};

////////////////////////////////////////////
// Smooth filter with fixed time constant //
////////////////////////////////////////////

smooth = si.smooth(ba.tau2pole(tau)) with { tau = 100e-3; };

////////////////////
// Multi-wave LFO //
////////////////////

// w=0: triangle, w=0.5: sine-triangle, w=1: sine
lfoWave(w, p) = ba.if(p<0.5, firstHalf(p), secondHalf(p)) with {
  firstHalf(p) = (triangle(p), sine(p)) : si.interpolate((2.*w) : min(1.));
  secondHalf(p) = (triangle(p), sine(p)) : si.interpolate(w);
  triangle(p) = rdtable(tablesize, triwaveform01(tablesize), int(p*tablesize)%tablesize);
  sine(p) = rdtable(tablesize, sinwaveform01(tablesize), int(p*tablesize)%tablesize);
  tablesize = 1<<16;
};

///////////////
// Waveforms //
///////////////

triwaveform(tablesize) = ba.if(p<0.25, 4*p, ba.if(p<0.75, -4*p+2, 4*p-4)) with {
  p = float(ba.time)/float(tablesize);
};

triwaveform01(tablesize) = triwaveform(tablesize) : +(1.) : *(0.5);
sinwaveform01(tablesize) = os.sinwaveform(tablesize) : +(1.) : *(0.5);

/////////////////////
// Phase generator //
/////////////////////

phasor01(f) = p letrec { 'p = wrap(p+f/ma.SR); };

/////////////
// Utility //
/////////////

wrap(p) = p-int(p);
