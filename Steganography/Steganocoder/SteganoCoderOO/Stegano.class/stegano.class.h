#ifndef STEGANOCLASS
#define STEGANOCLASS

#include <fstream>

enum error{OK,WRONG_BMP,TXT_SIZE_ERROR,UNKNOWN_ERROR=-1};

class Stegano {
public:

	Stegano(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename)
		:InBMPFile(InBMPFilename,std::ios::binary | std::ios::in),
		InTXTFile(InTXTFilename,std::ios::binary | std::ios::in),
		OutBMPFile(OutBMPFilename,std::ios::binary | std::ios::out) {
			inited=0;offset=0;width=0;height=0;capasity=0;messageSize=0;
	}

	Stegano(const char *InBMPFilename,const char *OutBMPFilename)
		:InBMPFile(InBMPFilename,std::ios::binary | std::ios::in),
		OutTXTFile(OutBMPFilename,std::ios::binary | std::ios::out) {
			inited=0;offset=0;width=0;height=0;capasity=0;messageSize=0;
	}

	virtual ~Stegano();

	bool encrypt() {
		if(!inited)
			return false;
		enc();
		return true;
	}

	bool decrypt() {
		if(!inited)
			return false;
		dec();
		return true;
	}

	int init();

private:
	Stegano(){};
	Stegano(const Stegano&);
	Stegano& operator=(const Stegano&);


protected:
	virtual void enc()=0;
	virtual void dec()=0;
	bool inited;
	UINT offset;
	UINT width;
	UINT height;
	UINT capasity;
	UINT messageSize;
	std::fstream InBMPFile;
	std::fstream InTXTFile;
	std::fstream OutBMPFile;
	std::fstream OutTXTFile;
};

class withKey {
protected:
	withKey(const char *key) {
		UINT seed=0;
		for(UINT j=0;j<strlen(key);j++)
			seed+=key[j];
		srand(seed);
	}
};

#endif
