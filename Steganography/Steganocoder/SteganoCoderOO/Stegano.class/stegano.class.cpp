#include "stdafx.h"
#include "stegano.class.h"

Stegano::~Stegano () {
	if(InBMPFile)
		InBMPFile.close();
	if(InTXTFile)
		InTXTFile.close();
	if(OutBMPFile)
		OutBMPFile.close();
	if(OutTXTFile)
		OutTXTFile.close();
}

void Stegano::init(const char *InBMPFilename,const char *InTXTFilename,const char *OutBMPFilename,const char *OutTXTFilename,const char *key) {
	if(InBMPFilename)
		InBMPFile.open(InBMPFilename,std::ios::binary | std::ios::in);
	if(InTXTFilename)
		InTXTFile.open(InTXTFilename,std::ios::binary | std::ios::in);
	if(OutBMPFilename)
		OutBMPFile.open(OutBMPFilename,std::ios::binary | std::ios::out);
	if(OutTXTFilename)
		OutTXTFile.open(OutTXTFilename,std::ios::binary | std::ios::out);
	if(key)	{
		UINT seed=0;
		for(UINT j=0;j<strlen(key);j++)
			seed+=key[j];
		srand(seed);
	}
	if((InBMPFile && InTXTFile && OutBMPFile) || (InBMPFile && OutTXTFile)) {
		
		BITMAPFILEHEADER sbfh;
		BITMAPINFOHEADER sbih;

		InBMPFile.read((char*)&sbfh,sizeof(BITMAPFILEHEADER));
		if(sbfh.bfType!='MB'){
			throw(WRONG_BMP);
		}
		InBMPFile.read((char*)&sbih,sizeof(BITMAPINFOHEADER));

		offset=sbfh.bfOffBits;
		width=sbih.biWidth;
		height=(sbih.biHeight>0) ? sbih.biHeight : -sbih.biHeight;

		capasity=(width*height*3/8)-offset-32;

		InBMPFile.seekg(0);
		for(UINT i=0;i<offset;i++)
			OutBMPFile.put(InBMPFile.get());

		if (InTXTFile && OutBMPFile) {
			InTXTFile.seekg(0,std::ios::end);
			messageSize=InTXTFile.tellg();
			InTXTFile.seekg(0,std::ios::beg);

			if(capasity<messageSize*8 || !messageSize) {
				throw(TXT_SIZE_ERROR);
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
				throw(UNKNOWN_ERROR);
		}
		return;
	}
	throw(UNKNOWN_ERROR);
}