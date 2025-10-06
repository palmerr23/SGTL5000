# Arduino SGTL5000 2x2 CODEC control library for Pico

A generic Arduino control library for the NXP SGTL5000 stereo channel CODEC. 

V1.0

Ported from https://github.com/PaulStoffregen/Audio

## Compatibility
Tested with Arduino Pico and Pico 2 with Arduino-pico 5.30 or later.

May work with other architectures, however I2S commands will likely differ.


## Single CODEC I2S operation 
I2S mode is the default for single codecs, however TDM may be selected using the i2sMode argument.

Avoid the more complex forms of the various function calls, accepting the default arguments where they are available, as some combinations of arguments may not be compatible.

## Available Hardware

The Teensy Audio Board (version C, D or D2) is compatible with this library.  https://www.pjrc.com/store/teensy3_audio.html or https://www.sparkfun.com/teensy-4-audio-shield-rev-d.html
# Function Reference

This library has been tested with with a the Arduino-Pico 5.30  6-bit I2S (left justified) driver in output-only and duplex modes.

### Constructor

```
SGTL5000 codec(I2C address); 
```

### Wire

Defining and initialising the Wire library is the responsibility of the user application. 

This must be completed before enable( ) is called.

### Function reference
The library uses the same commands as for the Teensy Audio Library version, see:

https://www.pjrc.com/teensy/gui/index.html?info=AudioControlSGTL5000

The only exception is the constructor requires the I2C address of the CODEC:

```
SGTL5000 codec(i2c_addr);
```

## Examples
- Basic operation I2S mode. Output only and full duplex with one channel pass-through.




