#ifndef _PRSKEY_H_
#define _PRSKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include "key.h"


/** C++ class for keys generation for PRS algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Mar 25th, 2009
*
*/
class PRSKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PRSKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    virtual ~PRSKey();


    /** Tells if this key is PRS key */
    virtual bool IsPRSKey() const { return true; }


    /** Apply PRS Key to _message and return modified message */
    std::string ApplyPRSKey( const std::string& _message ) const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
