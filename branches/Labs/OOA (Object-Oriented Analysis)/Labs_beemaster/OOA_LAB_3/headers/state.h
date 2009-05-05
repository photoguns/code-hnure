#ifndef STATE_H
#define STATE_H

#include "event.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////

class State
{
////////////////////////////////////////////////////////////////////////////////

public:

	virtual State* ProcessEvent(Event _event) = 0;

////////////////////////////////////////////////////////////////////////////////

	static void SetStates(std::vector<State*>& _states);
    static void DestroyStates();
	
////////////////////////////////////////////////////////////////////////////////

    static State* GetOnState();
    static State* GetOffState();
    static State* GetPauseState();

////////////////////////////////////////////////////////////////////////////////

    virtual bool IsOffState() const { return false; }
    virtual bool IsOnState() const { return false; }
    virtual bool IsPauseState() const { return false; }

////////////////////////////////////////////////////////////////////////////////

    void PrintStateInfo() const;

////////////////////////////////////////////////////////////////////////////////

protected:

	static int m_Timer;

////////////////////////////////////////////////////////////////////////////////

private:

	static std::vector<State*> m_States;

////////////////////////////////////////////////////////////////////////////////
};


////////////////////////////////////////////////////////////////////////////////

#endif