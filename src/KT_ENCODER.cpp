// 
// 
// 

#include "KT_ENCODER.h"

KT_ENCODER* KT_ENCODER::MyISR = 0;

KT_ENCODER::KT_ENCODER(int Lpin, int Rpin)
{
	MyISR = this;
	_Lpin = Lpin;
	_Rpin = Rpin;
}

void KT_ENCODER::begin(uint8_t Mode) {
	attachInterrupt(digitalPinToInterrupt(_Lpin), KT_ENCODER::updateISR_L, Mode);
	attachInterrupt(digitalPinToInterrupt(_Rpin), KT_ENCODER::updateISR_R, Mode);
}

bool KT_ENCODER::update(unsigned long sampleTime) {
	unsigned now = millis();
	if (now - prev_Time > sampleTime) {
		SpeedL = L_Count;
		SpeedR = R_Count;

		ReadingFlag = true;
		resetAll();
		prev_Time = now;
		return 1;
	}
	return 0;
}

unsigned long KT_ENCODER::getSpeed(MOTOR side,bool DoneRead) {
	unsigned long val;
	if (ReadingFlag) {
		switch (side)
		{
		case LEFT:
			val = SpeedL;
			break;
		case RIGHT:
			val = SpeedR;
			break;
		}		
	}
	if (DoneRead) {
		ReadingFlag = false;
	}

	return val;
}

void KT_ENCODER::updateISR_L() {
	if(MyISR != 0)
		MyISR->countL();
}

void KT_ENCODER::updateISR_R() {
	if (MyISR != 0)
		MyISR->countR();
}

void KT_ENCODER::countL() {
	L_Count++;
}

void KT_ENCODER::countR() {
	R_Count++;
}

void KT_ENCODER::resetL() {
	L_Count = 0;
}

void KT_ENCODER::resetR() {
	R_Count = 0;
}

void KT_ENCODER::resetAll() {
	L_Count = 0;
	R_Count = 0;
}