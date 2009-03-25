#include "stdafx.h"
#include "stegano.classes.h"

stegano::~stegano() {
	if(InBMPFile)
		InBMPFile.close();
	if(InTXTFile)
		InTXTFile.close();
	if(OutBMPFile)
		OutBMPFile.close();
	if(OutTXTFile)
		OutTXTFile.close();
}

int stegano::init() {
	if((InBMPFile && InTXTFile && OutBMPFile) || (InBMPFile && OutTXTFile)) {
		
		BITMAPFILEHEADER sbfh;
		BITMAPINFOHEADER sbih;

		InBMPFile.read((char*)&sbfh,sizeof(BITMAPFILEHEADER));
		if(sbfh.bfType!='MB'){
			return WRONG_BMP;
		}
		InBMPFile.read((char*)&sbih,sizeof(BITMAPINFOHEADER));

		offset=sbfh.bfOffBits;
		width=sbih.biWidth;
		height=(sbih.biHeight>0) ? sbih.biHeight : -sbih.biHeight;

		capasity=(width*height*3/8)-offset-32;

		InBMPFile.seekg(0);
		for(int i=0;i<offset;i++)
			OutBMPFile.put(InBMPFile.get());

		if (InTXTFile && OutBMPFile) {
			InTXTFile.seekg(0,std::ios::end);
			messageSize=InTXTFile.tellg();
			InTXTFile.seekg(0,std::ios::beg);

			if(capasity<messageSize*8) {
				return TXT_TOO_LARGE;
			}

			InBMPFile.seekg(offset);
			OutBMPFile.seekg(offset);
			int tmp=messageSize;
			UCHAR bf=0;
			for(int i=0;i<32;i++) {
				InBMPFile.read((char *)&bf,1);
				if(tmp%2)
					bf |= 1;
				else bf &= 0xFE;
				OutBMPFile.put(bf);
				tmp/=2;
			}

			while(!InBMPFile.eof()){
				InBMPFile.get((char &)bf);
				OutBMPFile.put(bf);
			}

			InBMPFile.clear();
			InBMPFile.seekg(offset+32);
			OutBMPFile.seekg(offset+32);
		}
		else if (OutTXTFile) {
			UCHAR bf=0;
			InBMPFile.seekg(offset);
			for(int i=0;i<32;i++) {
				InBMPFile.get((char &)bf);
				messageSize+=((bf%2)*(1<<i));
			}
			if(messageSize<0)
				return UNKNOWN_ERROR;
		}
		inited=1;
		return OK;
	}		
	return UNKNOWN_ERROR;
}

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
	for(int i=0;i<messageSize*8;i++) {
		InBMPFile.get((char &)bf);
		lett+=((bf%2)*(1<<(i%8)));
		if(!((i+1)%8)) {
			OutTXTFile<<lett;lett=0;
		}
	}
}

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
	for(int j=0;j<messageSize*8;j++) {
		InBMPFile.get((char &)bf);
		lett+=((bf%2)*(1<<(j%8)));
		InBMPFile.seekg(rand()%mod, std::ios::cur);
		if(!((j+1)%8)) {
			OutTXTFile<<lett;lett=0;
		}
	}

}

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
	kol=ceil(sqrt((double)fsizeb));
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
	kol=ceil(sqrt((double)fsizeb));
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