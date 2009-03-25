#include "stegano.class.h"

const short BlockLen=10;

class PRS: public Stegano, public withKey {
public:


	PRS(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename, const char *Key)
		:Stegano(InBMPFilename,InTXTFilename,OutBMPFilename),
		withKey(Key) {}
	
	PRS(const char *InBMPFilename, const char *OutBMPFilename, const char *Key)
	:Stegano(InBMPFilename,OutBMPFilename),
	withKey(Key) {}
	

private:
	UINT pm[BlockLen];
	void initPM();
	void enc();
	void dec();
	PRS();
};