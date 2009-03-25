#include "stdafx.h"
#include "LSB.class.h"

void LSB::enc() {

	UCHAR msg=0, bf=0;
	do {
		InTXTFile.get((char &)msg);
		for(int i=0;i<8;i++) {
			InBMPFile.get((char &)bf);
			if(msg%2)
				bf |= 1;
			else bf &= 0xFE;
			OutBMPFile.put(bf);
			msg/=2;
		}
	}
	while(!InTXTFile.eof());

}

void LSB::dec() {

	UCHAR bf=0,lett=0;
	for(UINT i=0;i<messageSize*8;i++) {
		InBMPFile.get((char &)bf);
		lett+=((bf%2)*(1<<(i%8)));
		if(!((i+1)%8)) {
			OutTXTFile<<lett;lett=0;
		}
	}
}