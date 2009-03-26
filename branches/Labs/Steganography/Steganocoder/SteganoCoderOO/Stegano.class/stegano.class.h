#ifndef STEGANOCLASS
#define STEGANOCLASS

#include <fstream>

enum error{WRONG_BMP,TXT_SIZE_ERROR,UNKNOWN_ERROR};

class Stegano {
public:

	Stegano():
	 offset(0),
	 width(0),
	 height(0),
	 capasity(0),
	 messageSize(0){}

	virtual ~Stegano();

	void encrypt(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename,  const char *key=0) {
		init( InBMPFilename, InTXTFilename, OutBMPFilename, 0,  key);
		enc();
	}

	void decrypt(const char *InBMPFilename,const char *OutTXTFilename,  const char *key=0) {
		init( InBMPFilename, 0, 0,OutTXTFilename, key);
		dec();
	}


private:
	void init(const char *,const char *,const char *,const char *,const char *);
	Stegano(const Stegano&);
	Stegano& operator=(const Stegano&);
	virtual void enc()=0;
	virtual void dec()=0;

protected:	
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

#endif
