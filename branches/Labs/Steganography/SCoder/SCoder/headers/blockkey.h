#ifndef _BLOCKKEY_H_
#define _BLOCKKEY_H_

////////////////////////////////////////////////////////////////////////////////

#ifndef _KEY_H_
#include "key.h"
#endif

/** C++ class for keys generation for block algorithm
*
*
*  @author  Roman Pasechnik
*  @since   March 25th, 2009
*  @updated March 25th, 2009
*
*/
class BlockKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    BlockKey();


    /** Destructor */
    virtual ~BlockKey();


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
};

#endif
