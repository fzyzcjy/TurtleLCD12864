/*
LCD12864
Created by Markos Kyritsis
This code is completely open source, and you may edit it however you like. 
Please support the Arduino community, and upload any bug fixes to the relative
page. 
Keep in mind that the code is for demonstration purposes only, I can't be
held responsible if your device suddenly zaps you into millions of little
atoms, and you live the rest of your existence in a quantum universe where
nothing makes sense anymore (you know, you exist in more than one place, changing
between matter and waves, while at the same time half your electrons are entangled
in some other point in space and time). 
Other than that, enjoy... =D
*/

#include "TurtleLCD12864.h"

#include <Arduino.h>
#include <inttypes.h>
#include <avr/pgmspace.h>

TurtleLCD12864::TurtleLCD12864() {
	initDelayTime = 80;
	drawDelayTime = 2;
}

void TurtleLCD12864::setPins(uint8_t tRS, uint8_t tRW, uint8_t vector) {
	digitalWrite(EN,1);
	delayns();
	digitalWrite(RS, tRS);
	digitalWrite(RW, tRW);
	for (int i = 7; i >= 0; i--) {
		digitalWrite(D[7-i],vector % 2);
		vector = vector/2;
	}
	delayns();
	digitalWrite(EN, 0);
	delayns();
}

void TurtleLCD12864::init(void) {
	isIniting = true;
	pinMode(RS, OUTPUT);
	pinMode(RW, OUTPUT);
	pinMode(EN, OUTPUT);
	for(int i = 0;i<8;++i){
		pinMode(D[i], OUTPUT);
	}

	setPins(0,0,0x5f);//5FH
	setPins(0,0,0x34);//34H
	setPins(0,0,0x30);//30H
	setPins(0,0,0x01);//01h
	setPins(0,0,0x06);//06h
	setPins(0,0,0x0c);//0ch
	setPins(0,0,B10111111);//try for gfx
	delayns();
	delayns();

	setPins(0,0,B00110100); // 8BIT Mode-4 ext gfx mode
	setPins(0,0,B00000010); // Vertical scroll
//  setPins(0,0,1,0,0,0,0,0,0,0); // SET 0,0
	delayns();
	delayns();

	setPins(0,0,B10000000); // SET DDRAM Y
	setPins(0,0,B10000000); // SET DDRAM X
	// Clear the Screen
	for (int j = 128; j <= 160; j++) {
		for (int i = 0; i <= 256; i+=8) {
			setPins(1,0,B00000000);
		}
		setPins(0,0,j);
		setPins(0,0,B10000000); // SET DDRAM X
	}
	setPins(0,0,B00110110); // 8BIT Mode-4 ext gfx mode
	isIniting = false;
}

//data.length = 32*32
void TurtleLCD12864::drawFullScreen(byte *data) {
	for (int line = 0; line < 32; line++) {
		/*setPins(0,0,line+128);
		setPins(0,0,B10000000); // SET DDRAM X at start again
		for (int i = 0; i < 32; i++) {
			setPins(1,0,data[line*32+i]);
		}*/
		drawLine(data + line*32, line);
	}
}

void TurtleLCD12864::delayns(void){
	delayMicroseconds((isIniting)?initDelayTime:drawDelayTime);
}

void TurtleLCD12864::beginDrawTransaction(){
	curDrawTransactionIndex = 0;
}

void TurtleLCD12864::endDrawTransaction(){}

void TurtleLCD12864::drawNextInTransaction(byte *data){
	int line = curDrawTransactionIndex++;
	drawLine(data,line);
}

void TurtleLCD12864::drawLine(byte *data, int line){
	setPins(0,0,line+128);
	setPins(0,0,B10000000); // SET DDRAM X at start again
	for (int i = 0; i < 32; i++) {
		setPins(1,0,data[i]);
	}
}

const TurtleLCD12864::byte TurtleLCD12864::RS = 17;
const TurtleLCD12864::byte TurtleLCD12864::RW = 16;
const TurtleLCD12864::byte TurtleLCD12864::EN = 18;
const TurtleLCD12864::byte TurtleLCD12864::D[8] = {8,9,10,11,4,5,6,7};
TurtleLCD12864 LCDT = TurtleLCD12864();
