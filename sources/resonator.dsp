import("stdfaust.lib");

numkeys = 88;
initialkey = 24;
depth = hslider("[1] Depth", 1, 0, 1, 0.01);

pitches(i) = hslider("[%n] Resonance frequency %j [unit:Hz]", ba.midikey2hz(i+initialkey), 0, 22000, 1) with { n = i*10+100; j = i+1; };
feedbacks(i) = hslider("[%n] Resonance feedback %j", 0, 0, 1, 0.001) with { n = i*10+101; j = i+1; };
bandwidths(i) = hslider("[%n] Bandwidth %j [unit:Hz]", 1, 0, 10, 0.01) with { n = i*10+102; j = i+1; };
gains(i) = hslider("[%n] Gain %j", 0, 0, 1, 0.01) with { n = i*10+103; j = i+1; };

resonator(f,r,g,b) = fi.bandpass(1, f-0.5*b, f+0.5*b) : fi.nlf2(f, r) : (_,!) : *(g);

process = _ <: (_, (sympathetic_resonance : *(depth))) :> + with {
  sympathetic_resonance = _ <: par(i, numkeys, band(i)) :> +;
  band(i) = resonator(pitches(i), feedbacks(i), bandwidths(i), gains(i));
};
