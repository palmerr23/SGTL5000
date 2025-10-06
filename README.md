# Arduino SGTL5000 2x2 CODEC control library for Pico

A generic Arduino control library for the NXP SGTL5000 stereo channel CODEC. 

V1.0

Ported from https://github.com/PaulStoffregen/Audio

## Compatibility

This library has been tested with with the Arduino-Pico (V5.30) 16-bit I2S (left justified) driver in output-only and duplex modes.

It may work with other architectures, however I2S commands will likely differ.

## I2S operation 
I2S mode is the default for single codecs, however TDM may be selected using the i2sMode argument.

## Available Hardware

The Teensy Audio Board (version C, D or D2) is compatible with this library.  https://www.pjrc.com/store/teensy3_audio.html or https://www.sparkfun.com/teensy-4-audio-shield-rev-d.html
## Function Reference


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




