#include "stdafx.h"
#include "PRI.class.h"

void PRI::enc() {

	int mod=capasity/messageSize/8;
	UCHAR msg=0,bf=0;
	while(!InTXTFile.eof()) {
		InTXTFile.get((char &)msg);
		for(int i=0;i<8;i++) {
			InBMPFile.get((char &)bf);
			if(msg%2)
				bf |= 1;
			else bf &= 0xFE;
			OutBMPFile.put(bf);
			int ofs=(rand()%mod);
			InBMPFile.seekg(ofs,std::ios::cur);
			OutBMPFile.seekg(ofs,std::ios::cur);
			msg/=2;
		}
	}

}

void PRI::dec() {

	int mod=capasity/messageSize/8;
	UCHAR bf=0,lett=0;
	for(UINT j=0;j<messageSize*8;j++) {
		InBMPFile.get((char &)bf);
		lett+=((bf%2)*(1<<(j%8)));
		InBMPFile.seekg(rand()%mod, std::ios::cur);
		if(!((j+1)%8)) {
			OutTXTFile<<lett;lett=0;
		}
	}

}
