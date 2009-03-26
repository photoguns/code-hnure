#include "stegano.class.h"

class Quantization: public Stegano {
	UINT tableOfQuant[510];
	void initTable();
	virtual void enc();
	virtual void dec();
};