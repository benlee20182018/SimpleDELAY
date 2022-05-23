# SimpleDELAY

This is an implementation of a simple stereo delay plug-in based on the JUCE framework.

The plug-in is writeen in C++, cross-platform and supports AU and VST3 formats.


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
