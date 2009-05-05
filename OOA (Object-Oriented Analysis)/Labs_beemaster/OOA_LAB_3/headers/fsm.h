#ifndef FSM_H
#define FSM_H

#include "state.h"

class FSM
{
public:
	FSM();
	~FSM();
	void ProcessEvent(Event _event);

private:
	State* m_State;
};

#endif