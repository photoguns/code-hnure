#ifndef STATEPAUSE_H
#define STATEPAUSE_H

#include "state.h"


////////////////////////////////////////////////////////////////////////////////

class StatePause: public State
{
////////////////////////////////////////////////////////////////////////////////

public:

    virtual bool IsPauseState() const { return true; }

////////////////////////////////////////////////////////////////////////////////

    virtual State* ProcessEvent(Event _event);

////////////////////////////////////////////////////////////////////////////////
};

#endif
