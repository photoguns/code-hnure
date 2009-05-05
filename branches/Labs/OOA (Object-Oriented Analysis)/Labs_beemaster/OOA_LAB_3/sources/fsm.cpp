#include "fsm.h"

#include "stateoff.h"
#include "stateon.h"
#include "statepause.h"

////////////////////////////////////////////////////////////////////////////////

FSM::FSM()
{
	std::vector<State*> states;
	states.push_back(new StateOff);
	states.push_back(new StateOn);
	states.push_back(new StatePause);

	State::SetStates(states);
	m_State = State::GetOffState();
}

////////////////////////////////////////////////////////////////////////////////

FSM::~FSM()
{
	State::DestroyStates();
}

////////////////////////////////////////////////////////////////////////////////

void FSM::ProcessEvent(Event _event)
{
	m_State = m_State->ProcessEvent(_event);
    m_State->PrintStateInfo();
}

////////////////////////////////////////////////////////////////////////////////
