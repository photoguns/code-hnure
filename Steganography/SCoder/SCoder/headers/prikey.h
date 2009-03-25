#ifndef _PRIKEY_H_
#define _PRIKEY_H_

////////////////////////////////////////////////////////////////////////////////

#ifndef _KEY_H_
#include "key.h"
#endif

/** C++ class for keys generation for PRI algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class PRIKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PRIKey();


    /** Destructor */
    virtual ~PRIKey();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
};

#endif