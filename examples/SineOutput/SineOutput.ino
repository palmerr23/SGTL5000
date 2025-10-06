//  SGTL5000 Sine output and optional input pass through
// Arduino-pico 5.3.0
//#define OUTPUT_ONLY
uint32_t sampleRate = 44100; // teensy standard
int sampleLength = 16;
#include <Wire.h>
#include <I2S.h>
#ifdef OUTPUT_ONLY
  I2S i2s(OUTPUT); 
#else
  I2S i2s(INPUT_PULLUP); //  bi-directional
#endif

uint8_t i2c_addr =  0x0A;
#include "sgtl5000.h"
SGTL5000 codec(i2c_addr);

// CODEC PINS
#define DOUT 21
#define DIN  22
#define WCLK 20
#define BCLK 19
#define MCLK 18


#define SDAPIN 4
#define SCLPIN 5

#define BUFLEN 1024
int16_t outBuf[2][BUFLEN]; // stereo

void setup(void) {
  Serial.begin(19200);
  while(!Serial)
			delay(10);
  Serial.println("SGTL5000 input/output");
  Serial.println("OUTPUT_ONLY -> sine on both channels");
  Serial.println("OUTPUT_ONLY -> L output from L input, sine on R output");
  Wire.setSDA(SDAPIN);
	Wire.setSCL(SCLPIN);
  Wire.begin();
  Wire.setClock(100000);

  int actualF =	fillSineBuffer(1000, 28000); // 1kHz, 2/3 max value
	Serial.printf("Frequency is %i\n", actualF);
  i2s.setSysClk(sampleRate);
#ifdef OUTPUT_ONLY
  i2s.setDATA(DOUT);
#else
  i2s.setDOUT(DOUT);
	i2s.setDIN(DIN);
#endif
  i2s.setBCLK(BCLK); // LRCLK (WCLK) pin = BCLK + 1
	i2s.setMCLK(MCLK);
  i2s.setMCLKmult(256);
  i2s.setBitsPerSample(sampleLength);
  i2s.setFrequency(sampleRate);
  i2s.begin();

  //  MCLK must be running before the chip will respond to I2C commands
  codec.enable();
  codec.volume(0.5);     // set the main volume...
  codec.dacVolume(1);    
  Serial.println("setup done");
}

int bufIndx = 0;
void loop() 
{
	int16_t l, r;
#ifdef OUTPUT_ONLY
	i2s.write16(outBuf[1][bufIndx], outBuf[1][bufIndx]); 
#else
	i2s.read16(&l, &r);
  i2s.write16(l, outBuf[1][bufIndx]); // left channel pass-through
#endif

	bufIndx = (bufIndx + 1) % BUFLEN;  
}

// frequency should be limited to < 1/2 sampleRate
// exactly fills the buffer with cycsTable cycles
// so actual frequency will differ from target
int fillSineBuffer(uint16_t freqTarget, int countMax)
{
  int cycsTable = 0.5 + 1.0 * freqTarget * BUFLEN / sampleRate; // round to closest integer
  int freq = cycsTable * sampleRate / BUFLEN;
	for(int i = 0; i < BUFLEN; i++)
		outBuf[1][i] = countMax * sin(i * 2.0 * 3.14159 * cycsTable / BUFLEN);
	return freq;
}
/*
unsigned int readReg(unsigned int reg)
{
	unsigned int val;
	Wire.beginTransmission(i2c_addr);
	Wire.write(reg >> 8);
	Wire.write(reg);
	if (Wire.endTransmission(false) != 0) return 0;
	if (Wire.requestFrom((int)i2c_addr, 2) < 2) return 0;
	val = Wire.read() << 8;
	val |= Wire.read();
	return val;
}
*/
