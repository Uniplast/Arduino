//This BlinkM library was created by Eric Townsend. Using this code is free. You may modify and use this code however you want.
//If you do use this code, if would be nice to mention me :)

//This library uses the Wire1 pins on the Due, and Wire for everything else.
//This library should be compatible with all Arduino SDK versions.
//If you're using the Due, you have to use a later version of the SDK.

#ifndef BlinkM_h
#define BlinkM_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

#include <Wire.h>

class BlinkM {
public:
	BlinkM();	//Default constructor.
	void setRGB(uint8_t addr, uint8_t R, uint8_t G, uint8_t B);
	void fadeRGB(uint8_t addr, uint8_t R, uint8_t G, uint8_t B);
	void fadeHSB(uint8_t addr, uint8_t H, uint8_t S, uint8_t B);
	void fadeRandRGB(uint8_t addr, uint8_t R, uint8_t G, uint8_t B);
	void fadeRandHSB(uint8_t addr, uint8_t H, uint8_t S, uint8_t B);
	void playScript(uint8_t addr, uint8_t scriptId, uint8_t rpt, uint8_t line);
	void stopScript(uint8_t addr);
	void setFadeSpeed(uint8_t addr, uint8_t speed);
	void setTimeAdjust(uint8_t addr, uint8_t time);
	void getCurrentRGB(int addr, uint8_t *R, uint8_t *G, uint8_t *B);
	void readScriptLine(int addr, uint8_t scriptId, uint8_t line, uint8_t *duration, uint8_t *command, uint8_t *arg1, uint8_t *arg2, uint8_t *arg3);
	void setScriptLengthRpt(uint8_t addr, uint8_t scriptId, uint8_t len, uint8_t rpt);
	void setLightAddress(uint8_t addr, uint8_t newAddr);
	void getLightAddress(uint8_t *addr);
	void getFirmwareVersion(int addr, uint8_t *majorVersion, uint8_t *minorVersion);
	void setStartParams(uint8_t addr, uint8_t mode, uint8_t scriptId, uint8_t rpt, uint8_t fadeSpeed, uint8_t timeAdj);
	void scanAddresses();
	void scanAddresses(int scanDelay);
private:
	TwoWire wireObject;
};

#endif