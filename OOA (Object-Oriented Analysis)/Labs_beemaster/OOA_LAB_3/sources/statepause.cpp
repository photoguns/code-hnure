#include "statepause.h"

////////////////////////////////////////////////////////////////////////////////

State* StatePause::ProcessEvent(Event _event)
{
    switch (_event)
    {
    case ADD_TIME:
        m_Timer += 1;
        return this;

    case SUB_TIME:
        if (m_Timer > 0)
            m_Timer -= 1;
        return this;

    case CLOSE_DOOR:
        if (m_Timer > 0)
            return GetOnState();
        else
            return GetOffState();

    default:
        return this;
    }
}

////////////////////////////////////////////////////////////////////////////////
