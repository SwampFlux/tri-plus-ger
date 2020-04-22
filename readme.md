# Tri+ger
An alternative firmware for the Qu-Bit Tri-ger

This is a work in progress. The current state of things is that 25 of the 32 pins on the tri-ger have been identified with just a few weird things going on.

## Goals
Qu-Bit set out to create a trigger module that embraces playing beats live and recording beats with slop. What they actually created is a trigger module with bad resolution. I loved the idea of the Tri-ger but once it was under my finger tips I absolutely hated it. Tri+ger attempts to rewrite the firmware to give the user the experience that was expected before they started reading the manual.

### Clock Input
The most requested feature of tri-ger was clock input. I believe this will be achieved through the tempo input, but if that is not possible, the tri-ger hardware does have a slave mode, and a 2hp expansion module for clocking could be another way to do this. Playing with jumpers without the 2hp expansion may be a way to toggle functionality. At this point, I just don't know what the expansion pins are connected to.

### Beat quantization
Instead of throwing out the slop completely, I'd like to meet qu-bit somewhere inbetween completely sloppy beats and perfectly quantized beats. I think that the clock division input will be a good way of doing this. Internally, my plan is to create many beat grids with ever finer divisions. As you record, beats will be added to every layer which will result in finer detailed layers keeping slop and less detailed layers sounding time-quantized. This method will likely also greatly increase the quality of recorded slop since the memory grid can be scaled to match the incoming clock signals.

### Extra Feature: Gate Weight
I have been designing a trigger module of my own, Probagate, that allows each beat in the sequence to have a weight and a parameter for filtering out lightweight steps. I will attempt to include this feature by way of some special button combination and/or taking over one of the CV inputs.
