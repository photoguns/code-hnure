#include "stdafx.h"
#include "BLOCK.class.h"
#include <cmath>

BLOCK::~BLOCK () {
	delete[] blx;
	delete[] bly;
	for(UINT i=0;i<kol;i++)
		delete[] masch[i];
	delete[] masch;
	for(int i=0;i<3;i++) {
		for(UINT j=0;j<width;j++) {
			delete[] RGBa[i][j];
		}
		delete[] RGBa[i];
	}
	delete[] RGBa;
}

void BLOCK::initRGB() {

	InBMPFile.seekg(offset);
	for(UINT i=0;i<height;i++)
		for(UINT j=0;j<width;j++)
			for(int k=0;k<3;k++)
				RGBa[k][j][i]=InBMPFile.get();

	for(UINT i=0;i<height;i++) {
		for(UINT j=0;j<width;j++) {
			for(int z=0;z<3;z++) {
				for(UINT k=0;k<kol-1;k++) {
					if(blx[k]<=j && blx[k+1]>j) {
						for(UINT a=0;a<kol-1;a++)
							if(bly[a]<=i && bly[a+1]>i) {
								masch[k][a] ^= RGBa[z][i][j] & 1;
								break;
							}
							break;
					}
				}
			}
		}
	}

}

void BLOCK::enc() {

	UINT fsizeb=messageSize*8;
	kol=static_cast<UINT>(ceil(sqrt((double)fsizeb)));
	modx=width/kol;
	mody=height/kol;
	blx=new UINT[kol]; bly=new UINT[kol];
	UCHAR **masch=new UCHAR*[kol];
	UCHAR ***RGBa=new UCHAR**[3];

	blx[0]=0; bly[0]=0;
	blx[kol-1]=width; bly[kol-1]=height;

	for(int i=0;i<3;i++) {
		RGBa[i]=new UCHAR*[width];
		for(UINT j=0;j<width;j++)
			RGBa[i][j]=new UCHAR[height];
	}

	for(UINT i=0;i<kol;i++) {
		masch[i]=new UCHAR[kol];
		ZeroMemory(masch[i],sizeof(masch[i]));
	}

	for(UINT i=1;i<kol-1;i++) {
		blx[i]=(rand()%(modx-1)+blx[i-1])+1;
		bly[i]=(rand()%(mody-1)+bly[i-1])+1;
	}

	initRGB();

	UCHAR msg=0;
	int k=0;
	for(UINT i=0;i<kol-1;i++)
		for(UINT j=0;j<kol-1;j++,((k==7)?k=0:k++)) {
			if(!k) {
				InTXTFile.get((char &)msg);
				if(InTXTFile.eof())
					break;
			}
			if((msg%2 && !masch[i][j]) || (!(msg%2) && masch[i][j]))
				RGBa[0][blx[j+1]/2][bly[i+1]/2] +=1;
			msg/=2;
		}
		OutBMPFile.seekg(offset+32);
		int cnt=32;
		for(UINT i=0;i<height;i++) {
			for(UINT j=0;j<width;j++) {
				for(k=0;k<3;k++) {
					if(!cnt)
						OutBMPFile.put(RGBa[k][j][i]);
					else cnt--;
				}
			}
		}
}

void BLOCK::dec() {

	UINT fsizeb=messageSize*8;
	kol=static_cast<UINT>(ceil(sqrt((double)fsizeb)));
	modx=width/kol;
	mody=height/kol;
	blx=new UINT[kol]; bly=new UINT[kol];
	UCHAR **masch=new UCHAR*[kol];
	UCHAR ***RGBa=new UCHAR**[3];

	blx[0]=0; bly[0]=0;
	blx[kol-1]=width; bly[kol-1]=height;

	for(int i=0;i<3;i++) {
		RGBa[i]=new UCHAR*[width];
		for(UINT j=0;j<width;j++)
			RGBa[i][j]=new UCHAR[height];
	}

	for(UINT i=0;i<kol;i++) {
		masch[i]=new UCHAR[kol];
		ZeroMemory(masch[i],sizeof(masch[i]));
	}

	for(UINT i=1;i<kol-1;i++) {
		blx[i]=(rand()%(modx-1)+blx[i-1])+1;
		bly[i]=(rand()%(mody-1)+bly[i-1])+1;
	}

	initRGB();

	int k=0;
	UCHAR lett=0;
	for(UINT i=0;i<kol-1;i++)
		for(UINT j=0;j<kol-1;j++,(k==7)?k=0:k++) {
			lett+=(((masch[i][j]) & 1)*(1<<k));
			if(k==7) {
				OutTXTFile<<lett;
				lett=0;
			}
		}

}