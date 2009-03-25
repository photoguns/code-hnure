#include "stdafx.h"
#include "PRS.class.h"

void PRS::initPM () {
	UINT t;
	bool match;

	pm[0]=rand()%BlockLen;
	for(int i=1;i<BlockLen;i++) {
		match=0;
		t=rand()%BlockLen;
		for(int j=0;j<i;j++) {
			if(pm[j]==t) {
				match=1;break;
			}
		}
		if(match) i--;
		else pm[i]=t;
	}
}

void PRS::enc() {

	initPM();

	UCHAR temp[BlockLen], smsg[BlockLen], bf=0;

	while(!InTXTFile.eof()) {
		ZeroMemory(temp,sizeof(temp));
		InTXTFile.read((char *)temp,sizeof(temp));
		for(int j=0;j<BlockLen;j++)
			smsg[j]=temp[pm[j]];
		for(int c=0;c<BlockLen;c++) {
			for(int i=0;i<8;i++) {
				InBMPFile.read((char *)&bf,1);
				if(smsg[c]%2)
					bf |= 1;
				else bf &= 0xFE;
				OutBMPFile.put(bf);
				smsg[c]/=2;
			}
		}
	}

}

void PRS::dec() {

	initPM();

	int tmp=messageSize;

	UCHAR temp[BlockLen], smsg[BlockLen], bf=0;

	ZeroMemory(smsg,sizeof(smsg));
	ZeroMemory(temp,sizeof(temp));
	while(!InBMPFile.eof() && tmp>0) {
		for(int i=0;i<BlockLen;i++) {
			for(int j=0;j<8;j++) {
				InBMPFile.get((char &)bf);
				smsg[i]+=((bf%2)*(1<<j));
			}
		}
		for(int i=0;i<BlockLen;i++)
			for(int j=0;j<BlockLen;j++) {
				if(pm[j]==i) {
					temp[i]=smsg[j];
					break;
				}
			}

			OutTXTFile.write((char*)temp,sizeof(temp));
			ZeroMemory(smsg,sizeof(smsg));
			ZeroMemory(temp,sizeof(temp));
			tmp-=BlockLen;
	}

}