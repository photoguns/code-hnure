#include "stdafx.h"
#include "Quantization.class.h"

void Quantization::initTable () {
	for(int i=0;i<510;i++) {
		tableOfQuant[i]=rand()%2;
	}
}


void Quantization::enc() {

	initTable ();

	UCHAR msg=0, bf1=0, bf2=0;
	char dif=0;
	while(!InTXTFile.eof()) {
		InTXTFile.get((char &)msg);
		for(int i=0;i<8;i++) {
			InBMPFile.get((char &)bf1);
			InBMPFile.get((char &)bf2);
			dif=bf1-bf2;
			while(msg%2 != tableOfQuant[dif+255])
				(dif==254)?dif=0:dif++;
			bf2=bf1-dif;
			OutBMPFile.seekg(((int)InBMPFile.tellg())-1);
			OutBMPFile.put(bf2);
			msg/=2;
		}
	}

}

void Quantization::dec() {

	initTable ();

	UCHAR lett=0, bf1=0, bf2=0;
	char dif=0;
	for(int i=0;i<messageSize*8;i++) {
		InBMPFile.get((char &)bf1);
		InBMPFile.get((char &)bf2);
		dif=bf1-bf2;
		lett+=(((tableOfQuant[dif+255])%2)*(1<<(i%8)));
		if(!((i+1)%8)) {
			OutTXTFile<<lett;lett=0;
		}
	}

}