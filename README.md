# SGTL5000 2x2 CODEC control library for Arduino Pico

V1.0

A generic Arduino control library for the NXP SGTL5000 stereo channel CODEC, specifically intended for use with Pico and Pico 2 processors under Arduino-Pico v5.30 or later.

Ported from https://github.com/PaulStoffregen/Audio

## Compatibility

This library has been tested with with the Arduino-Pico (V5.30) 16-bit I2S (left justified) driver in output-only and duplex modes using a Version C Teensy Audio Board.

44.1, 48 and 96kHz sample rates have been tested.

The code may work with other architectures and modes, however the platform's I2S commands will likely differ from those used in the example.

## I2S operation 
Only signed 16-bit stereo I2S mode is implemented.

## Available Hardware

The Teensy Audio Board (version C, D or D2) is compatible with this library.  https://www.pjrc.com/store/teensy3_audio.html or https://www.sparkfun.com/teensy-4-audio-shield-rev-d.html
## Function Reference


### Wire
Defining and initialising the Wire library is the responsibility of the user application. 

This must be completed before enable( ) is called.

### Function reference
The library uses the same commands as for the Teensy Audio Library version, see:

https://www.pjrc.com/teensy/gui/index.html?info=AudioControlSGTL5000

The exceptions are: 

SGTL clock master mode and the PLL are disabled, requiring a synchronized MCLK of Fs x 256 or 512 for <= 48kHz, and 256 for 96kHz operation.


The constructor requires the I2C address of the CODEC.
```
SGTL5000 codec(i2c_addr);
```
The sample rate and sysClck frequency should be issued before enable()
```
setSampleRate(uint32_t sampleRate);
```
```
setSysClk(uint32_t sampleRate);
```

## Examples
- Basic operation I2S mode. Output only and full duplex with one channel pass-through.




