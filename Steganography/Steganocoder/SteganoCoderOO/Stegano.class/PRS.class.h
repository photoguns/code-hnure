#include "stegano.class.h"

const short BlockLen=10;

class PRS: public Stegano {
	UINT pm[BlockLen];
	void initPM();
	virtual void enc();
	virtual void dec();
};