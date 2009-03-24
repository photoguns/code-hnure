#include "stegano.class.h"

class BLOCK: public Stegano, public withKey {
public:

	BLOCK(const char *InBMPFilename, const char *InTXTFilename, const char *OutBMPFilename, const char *Key)
		:Stegano(InBMPFilename,InTXTFilename,OutBMPFilename),
		withKey(Key) {}
	
	BLOCK(const char *InBMPFilename, const char *OutBMPFilename, const char *Key)
	:Stegano(InBMPFilename,OutBMPFilename),
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