# SimpleDELAY

This is an implementation of a simple stereo delay plug-in based on the JUCE framework.

The plug-in is writen in C++, cross-platform and supports AU and VST3 formats.

The core delay component is almost entirely based on the delay line found in the JUCE string model tutorial 
(https://docs.juce.com/master/tutorial_dsp_delay_line.html#tutorial_dsp_delay_line_implement_delay_line). 

The delay line is a simple circular buffer design that also leverages a JUCE highpass filter.
The result is very sweet and smooth sounding delay. 

For this application, the original interface was extended to support control of feedback, wet and gain levels.


## Controls

### Left/Right Delay Time:

Sets the left and right channel delay times in seconds. Maxium delay time is 2 seconds and can be changed in 1ms increments.

### Feedback:

Sets the gain level of the signal that is fed back into the delay lines.

### Wet Level:

Sets the gain level of the wet signal.

### Gain:

Sets the trim level percentage in case the signal is too hot.

### Reset Delay Settings:

Sets all controls back to factory defaults.
