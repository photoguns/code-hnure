#include "stdafx.h"
#include "BLOCK.class.h"
#include <cmath>

void BLOCK::enc() {

	int mod=capasity/messageSize/8;
	UCHAR msg=0,bf=0;
	bool parity(false);
	int BlockLen=rand()%mod;
	while(!InTXTFile.eof()) {
		InTXTFile.get((char &)msg);
		for(int i=0;i<8;i++) {
			for(int j=0;j<BlockLen;j++) {
				InBMPFile.get((char &)bf);
				parity ^= bf & 1;
			}
			if((msg%2) ^ parity) {
				bf ^= 1;
				OutBMPFile.seekg(((int)InBMPFile.tellg())-1);
				OutBMPFile.put(bf);
			}
			parity=0;
			msg/=2;
			BlockLen=rand()%mod;
		}
	}
	
}

void BLOCK::dec() {

	int mod=capasity/messageSize/8;
	UCHAR bf=0,lett=0;
	bool parity(false);
	int BlockLen=rand()%mod;
	for(UINT j=0;j<messageSize*8;j++) {
		for(int i=0;i<BlockLen;i++) {
			InBMPFile.get((char &)bf);
			parity ^= bf & 1;
		}
		lett+=(parity*(1<<(j%8)));
		parity=0;
		BlockLen=rand()%mod;
		if(!((j+1)%8)) {
			OutTXTFile<<lett;lett=0;
		}
	}

}