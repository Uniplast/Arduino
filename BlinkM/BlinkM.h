//This BlinkM library was created by Eric Townsend. Using this code is free. You may modify and use this code however you want.
//If you do use this code, it would be nice to mention me :)

//This library uses the Wire1 pins on the Due, and Wire for everything else.
//This library should be compatible with all Arduino SDK versions.
//If you're using the Due, you have to use a later version of the SDK.

#ifndef BlinkM_h
#define BlinkM_h

#include <Arduino.h>
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

#if defined (__SAM3X8E__)
	TwoWire wireObject = Wire1;
#else
	TwoWire wireObject = Wire;
#endif
};

BlinkM::BlinkM() {
	wireObject.begin();
}

//Set BlinkM Light To An Immediate RGB Color.
void BlinkM::setRGB(uint8_t addr, uint8_t R, uint8_t G, uint8_t B) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x6E);
	wireObject.write(R);
	wireObject.write(G);
	wireObject.write(B);
	wireObject.endTransmission();
}

//Fade BlinkM From Current Color To A New RGB Color.
void BlinkM::fadeRGB(uint8_t addr, uint8_t R, uint8_t G, uint8_t B) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x63);
	wireObject.write(R);
	wireObject.write(G);
	wireObject.write(B);
	wireObject.endTransmission();
}

//Same As Previous, Except It's HSB Instead Of RGB.
void BlinkM::fadeHSB(uint8_t addr, uint8_t H, uint8_t S, uint8_t B) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x68);
	wireObject.write(H);
	wireObject.write(S);
	wireObject.write(B);
	wireObject.endTransmission();
}

//Fade BlinkM From Current Color To Random RGB Color.
void BlinkM::fadeRandRGB(uint8_t addr, uint8_t R, uint8_t G, uint8_t B) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x43);
	wireObject.write(R);
	wireObject.write(G);
	wireObject.write(B);
	wireObject.endTransmission();
}

//Same As Previous, Except It's HSB Instead Of RGB.
void BlinkM::fadeRandHSB(uint8_t addr, uint8_t H, uint8_t S, uint8_t B) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x48);
	wireObject.write(H);
	wireObject.write(S);
	wireObject.write(B);
	wireObject.endTransmission();
}

//Play A Pre-Programmed Script.
void BlinkM::playScript(uint8_t addr, uint8_t scriptId, uint8_t rpt, uint8_t line) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x70);
	wireObject.write(scriptId);
	wireObject.write(rpt);
	wireObject.write(line);
	wireObject.endTransmission();
}

//Stop The Currently Playing Script.
void BlinkM::stopScript(uint8_t addr) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x6F);
	wireObject.endTransmission();
}

//Set Speed At Which BlinkM Fades From Color To Color.
void BlinkM::setFadeSpeed(uint8_t addr, uint8_t speed) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x66);
	wireObject.write(speed);
	wireObject.endTransmission();
}

//Set Playback Speed Of Pre-Programmed Scripts.
//Takes A Signed Byte As Argument.
//Argument Is Treated As An Additive Adjustment.
//Using '0' Will Reset The Time Adjust.
void BlinkM::setTimeAdjust(uint8_t addr, uint8_t time) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x74);
	wireObject.write(time);
	wireObject.endTransmission();
}

//Get Current RGB Color BlinkM Is Currently Displaying.
void BlinkM::getCurrentRGB(int addr, uint8_t *R, uint8_t *G, uint8_t *B) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x67);
	wireObject.endTransmission();
	wireObject.requestFrom(addr, 3);

	*R = wireObject.read();
	*G = wireObject.read();
	*B = wireObject.read();
}

//Read User-Selected Line From Pre-Programmed Script.
void BlinkM::readScriptLine(int addr, uint8_t scriptId, uint8_t line, uint8_t *duration, uint8_t *command, uint8_t *arg1, uint8_t *arg2, uint8_t *arg3) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x52);
	wireObject.write(scriptId);
	wireObject.write(line);
	wireObject.endTransmission();
	wireObject.requestFrom(addr, 5);

	*duration = wireObject.read();
	*command = wireObject.read();
	*arg1 = wireObject.read();
	*arg2 = wireObject.read();
	*arg3 = wireObject.read();
}

//Sets Length Of Written Script And How Many Times To Repeat The Script.
void BlinkM::setScriptLengthRpt(uint8_t addr, uint8_t scriptId, uint8_t len, uint8_t rpt) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x4C);
	wireObject.write(scriptId);
	wireObject.write(len);
	wireObject.write(rpt);
	wireObject.endTransmission();
}

//Sets BlinkM's I2C Address.
void BlinkM::setLightAddress(uint8_t addr, uint8_t newAddr) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x41);
	wireObject.write(newAddr);
	wireObject.write(0xD0);
	wireObject.write(0xD0);
	wireObject.write(newAddr);
	wireObject.endTransmission();
}

//Query's BlinkM's I2C Address.
void BlinkM::getLightAddress(uint8_t *addr) {
	wireObject.beginTransmission(0);
	wireObject.write(0x61);
	wireObject.endTransmission();

	wireObject.requestFrom(0, 1);
	*addr = wireObject.read();
}

//Get BlinkM's Firmware Version (Major & Minor).
void BlinkM::getFirmwareVersion(int addr, uint8_t *majorVersion, uint8_t *minorVersion) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x5A);
	wireObject.endTransmission();

	wireObject.requestFrom(addr, 2);
	*majorVersion = wireObject.read();
	*minorVersion = wireObject.read();
}

//Sets The Boot-Up Actions For BlinkM.
//Arg1 <mode>: 0 Will Do Nothing, 1 Plays Script.
//Arg2 <scriptID>: Script To Play.
//Arg3 <rpt>: Number Of Repetitions For Script.
//Arg4 <fadeSpeed>: Fade Speed For Script.
//Arg5 <timeAdj>: Time Adjust For Script.
void BlinkM::setStartParams(uint8_t addr, uint8_t mode, uint8_t scriptId, uint8_t rpt, uint8_t fadeSpeed, uint8_t timeAdj) {
	wireObject.beginTransmission(addr);
	wireObject.write(0x42);
	wireObject.write(mode);
	wireObject.write(scriptId);
	wireObject.write(rpt);
	wireObject.write(fadeSpeed);
	wireObject.write(timeAdj);
	wireObject.endTransmission();
}

//Scans I2C Bus For All Connected BlinkMs
void BlinkM::scanAddresses() {
	for (byte i = 1; i < 127; i++) {
		wireObject.beginTransmission(i);
		if (wireObject.endTransmission() == 0) {
			Serial.print("Found Light: ");
			Serial.println(i);
		}
		delay(10);
	}
}

//Same As Above, But Has User-Defined Delay Between Each Scan.
void BlinkM::scanAddresses(int scanDelay) {
	for (byte i = 1; i < 127; i++) {
		wireObject.beginTransmission(i);
		if (wireObject.endTransmission() == 0) {
			Serial.print("Found Light: ");
			Serial.println(i);
		}
		delay(scanDelay);
	}
}
#endif