![Tri+ger photograph](https://repository-images.githubusercontent.com/256033709/fc436680-84a4-11ea-8528-825dbfbbbdbb)

# Tri+ger

An alternative firmware for the Qu-Bit Tri-ger eurorack module.

This is a work in progress. See the issues section for details on what's still in the works.

![Build Status](https://github.com/MicroWrave/tri-plus-ger/workflows/Build/badge.svg)
[![Open Issues](https://img.shields.io/github/issues/MicroWrave/tri-plus-ger)](https://github.com/MicroWrave/tri-plus-ger/issues)
![Arduino Pins](https://img.shields.io/badge/Arduino%20pins-32%20of%2032-green?logo=arduino)
![CV Inputs](https://img.shields.io/badge/CV%20Inputs-6%20of%206-green)
![CV Outputs](https://img.shields.io/badge/CV%20Outputs-3%20of%203-green)
![LEDs](https://img.shields.io/badge/LEDs-16%20of%2016-green)
![Knobs](https://img.shields.io/badge/Knobs-3%20of%203-green)
![Daisy Chain Pins](https://img.shields.io/badge/Daisy%20Chain%20pins-5%20of%205-green)

## Goals

Qu-Bit set out to create a trigger module that embraces playing beats live and recording beats that have a human touch. I loved the idea of the Tri-ger but once it was under my finger tips, I hated trying to stay in time with the rest of my rack. Tri+ger is alternative firmware that attempts to give me the user experience that I expected before I opened the box. Plus a little extra. But all within the limits of what the Tri-ger is, and respecting/re-thinking its original goals with the hindsight of using one.

### Reversable

Tri+ger attempts to make enhancements to the Tri-ger module without the need to permanently change the front panel, without cutting any traces, and without soldering. Scripts are provided to restore your module to the factory settings at any time—especially useful if you're trying out experimental builds. A removable sticker will be available to change the name on the front panel from Tri-ger to Tri+ger.

### Clock Input

The most requested feature of Tri-ger was clock input. Tri+ger adds clock detection at 1,2,4,8,16 or 24ppqn. I believe this can be achieved through the tempo input. If that is not possible the clock division cv input will be used.

### Beat Quantization

I'd like to meet Qu-Bit somewhere in-between sloppy humanized beats and perfectly quantized beats. I think that the clock division input will be a good way of doing this. Internally, Tri+ger uses a 24ppqn grid that is stretched across the 16 steps. As you record, beats will be added to a 24ppqn cell which keeping slop. As you divide the clock more, cells are grouped and OR compared to time-quantize triggers to the closest beat. This method will allow you to listen quantized and then un-quantize.

### Extra Feature: Gate Weight

I have been designing a step sequencer module of my own called [Probagate](https://github.com/MicroWrave/Probagate) that allows each beat in the sequence to have a weight. This feature is included in Tri+ger through some slightly esoteric combinations of button+dial combinations that have yet to be decided.

### A Note About Tri-ger 2

[A second version of the Tri-ger was revealed at Superbooth 2018](https://youtu.be/fCQBjFuuDRg) to be distributed by it's original designer [Jason H. J. Lim](https://github.com/jhjlim) of [Intruo Modular](https://www.instruomodular.com). If you are interested in getting a Tri-ger that does not need alternative firmware in order to have clock input, express your interest in the official re-release. Tri+ger is in no way meant to replace that effort or beat it to the punch. If anything, I hope it helps.

### A Note About Licensing & Rights

This repository has a [GNU General Public License v3.0](https://github.com/MicroWrave/tri-plus-ger/blob/master/LICENSE). It is NOT FOR SALE. Clock pattern detection code was borrowed from [Emilie Gillet's stmlib](https://github.com/pichenettes/stmlib/blob/fd5a4203acf7741f8e13bd4c067ac465bfd1bf25/algorithms/pattern_predictor.h) and modified to work with Arduino. The original is under [MIT License](https://github.com/pichenettes/stmlib/blob/fd5a4203acf7741f8e13bd4c067ac465bfd1bf25/LICENSE). The MIT copyright notice and permission notice are included in the [pattern detection file](https://github.com/MicroWrave/tri-plus-ger/blob/master/src/peaks_pattern_predictor.h).

### See Also
- [Probagate](https://github.com/MicroWrave/Probagate) a eurorack module which will turn Tri+ger's special features back into hardware
- [Tri+ger Muffwiggler Forum thread](https://www.muffwiggler.com/forum/viewtopic.php?f=16&t=231526&p=3258064#p3258064)
- [Richland Synth Fest 2020 talk](https://www.twitch.tv/videos/664368287) in which I explain my firmware hacking process
- [Jason H. J. Lim](https://github.com/jhjlim) designed the original Tri-ger
- [Qu-Bit Electronics](https://github.com/Qu-Bit-Electronix) manufactured the original Tri-ger
