#include <fstream>
#include <cmath>

enum error{OK,WRONG_BMP,TXT_TOO_LARGE,UNKNOWN_ERROR=-1};

const short BlockLen=10;

class stegano {
public:

	stegano(){};

	explicit stegano(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename)
		:InBMPFile(InBMPFilename,std::ios::binary | std::ios::in),
		InTXTFile(InTXTFilename,std::ios::binary | std::ios::in),
		OutBMPFile(OutBMPFilename,std::ios::binary | std::ios::out) {
			inited=0;offset=0;width=0;height=0;capasity=0;messageSize=0;
	}

	explicit stegano(const char *InBMPFilename,const char *OutBMPFilename)
		:InBMPFile(InBMPFilename,std::ios::binary | std::ios::in),
		OutTXTFile(OutBMPFilename,std::ios::binary | std::ios::out) {
			inited=0;offset=0;width=0;height=0;capasity=0;messageSize=0;
	}

	virtual ~stegano();

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
	stegano(const stegano&);
	stegano& operator=(const stegano&);


protected:
	virtual void enc()=0;
	virtual void dec()=0;
	bool inited;
	int offset;
	UINT width;
	UINT height;
	int capasity;
	int messageSize;
	std::fstream InBMPFile;
	std::fstream InTXTFile;
	std::fstream OutBMPFile;
	std::fstream OutTXTFile;
};

class withKey {
public:
	explicit withKey(const char *key) {
		UINT seed=0;
		for(UINT j=0;j<strlen(key);j++)
			seed+=key[j];
		srand(seed);
	}
private:
	withKey();
};

class LSB: public stegano {
public:


	explicit LSB(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename)
		:stegano(InBMPFilename,InTXTFilename,OutBMPFilename) {
	}

	explicit LSB(const char *InBMPFilename, const char *OutBMPFilename)
		:stegano(InBMPFilename,OutBMPFilename) {
	}


private:
	void enc();
	void dec();
	LSB();
};

class PRI: public stegano, public withKey {
public:


	explicit PRI(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename, const char *Key)
		:stegano(InBMPFilename,InTXTFilename,OutBMPFilename),
		withKey(Key) {
	}

	explicit PRI(const char *InBMPFilename, const char *OutBMPFilename, const char *Key)
		:stegano(InBMPFilename,OutBMPFilename),
		withKey(Key) {
	}


private:
	void enc();
	void dec();
	PRI();
};

class PRS: public stegano, public withKey {
public:


	explicit PRS(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename, const char *Key)
		:stegano(InBMPFilename,InTXTFilename,OutBMPFilename),
		withKey(Key) {
	}

	explicit PRS(const char *InBMPFilename, const char *OutBMPFilename, const char *Key)
		:stegano(InBMPFilename,OutBMPFilename),
		withKey(Key) {
	}


private:
	UINT pm[BlockLen];
	void initPM();
	void enc();
	void dec();
	PRS();
};

class BLOCK: public stegano, public withKey {
public:

	explicit BLOCK(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename, const char *Key)
		:stegano(InBMPFilename,InTXTFilename,OutBMPFilename),
		withKey(Key) {}

	explicit BLOCK(const char *InBMPFilename, const char *OutBMPFilename, const char *Key)
		:stegano(InBMPFilename,OutBMPFilename),
		withKey(Key) {}

	~BLOCK();


private:
	UINT *blx,*bly;
	UINT kol;
	UINT modx;
	UINT mody;
	UCHAR **masch;
	UCHAR ***RGBa;
	void initRGB();
	void enc();
	void dec();
	BLOCK();
};