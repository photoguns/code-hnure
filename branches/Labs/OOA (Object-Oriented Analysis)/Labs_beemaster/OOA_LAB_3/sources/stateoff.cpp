#include "stateoff.h"

////////////////////////////////////////////////////////////////////////////////

State* StateOff::ProcessEvent(Event _event)
{
    switch (_event)
    {
    case ADD_TIME:
        m_Timer += 1;
        return GetOnState();

    case OPEN_DOOR:
        return GetPauseState();

    default:
        return this;
    }
}

////////////////////////////////////////////////////////////////////////////////
