#include "TurtleLCD12864.h"

bool b=0;
unsigned char buf[32];

void setup(){
	LCDT.init();
}

void loop(){
	LCDT.beginDrawTransaction();
	for(int i=0;i<2;++i){
		for(int j = 0;j<32;++j){
			buf[j] = (b ^ (j%16<8) ^ (i<1))?0xFF:0;
		}
		for(int j = 0;j<16;++j){
			LCDT.drawNextInTransaction(buf);
		}
	}
	LCDT.endDrawTransaction();
    b=!b;
    delay(1000/10);
}
