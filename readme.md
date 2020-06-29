![Tri+ger photograph](https://repository-images.githubusercontent.com/256033709/fc436680-84a4-11ea-8528-825dbfbbbdbb)

# Tri+ger

An alternative firmware for the Qu-Bit Tri-ger eurorack module.

This is a work in progress. See the issues section for details on what's still in the works.

[![Build Status](https://travis-ci.org/MicroWrave/tri-ger-plus.svg?branch=master)](https://travis-ci.org/MicroWrave/tri-ger-plus)
[![Open Issues](https://img.shields.io/github/issues/MicroWrave/tri-plus-ger)](https://github.com/MicroWrave/tri-plus-ger/issues)
![Arduino Pins](https://img.shields.io/badge/Arduino%20pins-32%20of%2032-green?logo=arduino)
![CV Inputs](https://img.shields.io/badge/CV%20Inputs-6%20of%206-green)
![CV Outputs](https://img.shields.io/badge/CV%20Outputs-3%20of%203-green)
![LEDs](https://img.shields.io/badge/LEDs-16%20of%2016-green)
![Knobs](https://img.shields.io/badge/Knobs-3%20of%203-green)
![Daisy Chain Pins](https://img.shields.io/badge/Daisy%20Chain%20pins-5%20of%205-green)

## Goals

Qu-Bit set out to create a trigger module that embraces playing beats live and recording beats with slop. What they actually created is a trigger module with bad resolution. I loved the idea of the Tri-ger but once it was under my finger tips I absolutely hated it. Tri+ger attempts to rewrite the firmware to give the user the experience that was expected before they started reading the manual and perhaps add novel features that I was working on as an answer to this otherwise great piece of hardware.

### Clock Input

The most requested feature of tri-ger was clock input. I believe this will be achieved through the tempo input, but if that is not possible, the tri-ger hardware does have a slave mode, and a 2hp expansion module for clocking could be another way to do this. Playing with jumpers without the 2hp expansion may be a way to toggle functionality. At this point, I just don't know what the expansion pins are connected to.

### Beat Quantization

Instead of throwing out the slop completely, I'd like to meet QU-Bit somewhere inbetween completely sloppy beats and perfectly quantized beats. I think that the clock division input will be a good way of doing this. Internally, my plan is to create many beat grids with ever finer divisions. As you record, beats will be added to every layer which will result in finer detailed layers keeping slop and less detailed layers sounding time-quantized. This method will likely also greatly increase the quality of recorded slop since the memory grid can be scaled to match the incoming clock signals.

### Extra Feature: Gate Weight

I have been designing a trigger module of my own, Probagate, that allows each beat in the sequence to have a weight and a parameter for filtering out lightweight steps. I will attempt to include this feature by way of some special button combination and/or taking over one of the CV inputs.

### See Also

- [Tri+ger Muffwiggler Forum thread](https://www.muffwiggler.com/forum/viewtopic.php?f=16&t=231526&p=3258064#p3258064)
- [Richland Synth Fest 2020 talk](https://www.twitch.tv/videos/664368287)
