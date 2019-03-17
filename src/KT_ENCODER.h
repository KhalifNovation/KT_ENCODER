// KT_ENCODER.h

#ifndef _KT_ENCODER_h
#define _KT_ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum MOTOR
{
	LEFT,
	RIGHT
};

class KT_ENCODER
{
public:
	bool ReadingFlag = false;
	int _Lpin,_Rpin;
	volatile unsigned int L_Count, R_Count = 0;
	unsigned int SpeedL;
	unsigned int SpeedR;
	unsigned long prev_Time;

private:


public:
	KT_ENCODER(int Lpin, int Rpin);
	void begin(uint8_t Mode);
	void resetL();
	void resetR();
	void resetAll();

	bool update(unsigned long sampleTime);
	unsigned long getSpeed(MOTOR side, bool DoneRead);
	
private:
	static KT_ENCODER* MyISR;
	
	void countL();
	void countR();

	static void updateISR_L();
	static void updateISR_R();

};

#endif

