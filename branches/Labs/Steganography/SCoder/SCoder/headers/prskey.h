#ifndef _PRSKEY_H_
#define _PRSKEY_H_

////////////////////////////////////////////////////////////////////////////////

#ifndef _KEY_H_
#include "key.h"
#endif

/** C++ class for keys generation for PRS algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class PRSKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PRSKey();


    /** Destructor */
    virtual ~PRSKey();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
};

#endif
