#include "stateon.h"

////////////////////////////////////////////////////////////////////////////////

State* StateOn::ProcessEvent(Event _event)
{
    switch (_event)
    {
    case OPEN_DOOR:
        return GetPauseState();

    case ADD_TIME:
        m_Timer += 1;
        return this;

    case SUB_TIME:
        m_Timer -= 1;
        if (m_Timer == 0)
            return GetOffState();
        else
            return this;

    case DO_NOTHING:
        m_Timer -= 1;
        if (m_Timer == 0)
            return GetOffState();
        else
            return this;

    default:
        return this;
    }
}

////////////////////////////////////////////////////////////////////////////////
