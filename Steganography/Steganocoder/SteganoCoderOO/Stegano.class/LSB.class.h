#include "stegano.class.h"

class LSB: public Stegano {
public:


	LSB(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename )
		:Stegano(InBMPFilename,InTXTFilename,OutBMPFilename) {}

	LSB(const char *InBMPFilename, const char *OutBMPFilename)
	:Stegano(InBMPFilename,OutBMPFilename) {}

private:
	void enc();
	void dec();
	LSB();
};
