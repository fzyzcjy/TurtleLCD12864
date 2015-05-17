/*
Based on LCD12864 Created by Markos Kyritsis.
Advanced by Turtle (China, Fuzhou No.1 Middle School).
Here is my blog: http://www.cnblogs.com/turtlegood/
*/

#ifndef	TurtleLCD12864_h
#define TurtleLCD12864_h
#include <avr/pgmspace.h>
#include <inttypes.h>

class TurtleLCD12864 {
public:
	typedef unsigned char byte;
	TurtleLCD12864();
	void init();
	void drawFullScreen(byte *data);
	void beginDrawTransaction();
	void endDrawTransaction();
	void drawNextInTransaction(byte *data);
private:
	void drawLine(byte *data, int line);
	void delayns();
	void setPins(uint8_t tRS, uint8_t tRW, uint8_t vector);
private:
	byte initDelayTime,drawDelayTime;
	bool isIniting;
	int curDrawTransactionIndex;
private:
	static const byte RS;
	static const byte RW;
	static const byte EN;
	static const byte D[8];
};
extern TurtleLCD12864 LCDT;
#endif
