#include "stegano.class.h"

class PRI: public Stegano, public withKey {
public:


	PRI(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename, const char *Key)
		:Stegano(InBMPFilename,InTXTFilename,OutBMPFilename),
		withKey(Key) {}
	
	PRI(const char *InBMPFilename, const char *OutBMPFilename, const char *Key)
	:Stegano(InBMPFilename,OutBMPFilename),
	withKey(Key) {}
	

private:
	void enc();
	void dec();
	PRI();
};
