#ifndef _ECHOKEY_H_
#define _ECHOKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "key.h"


/** C++ class for keys generation for ECHO algorithm
*
*
*  @author  Roman Pasechnik
*  @since   May 27th, 2009
*  @updated May 27th, 2009
*
*/
class EchoKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    EchoKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    virtual ~EchoKey();


    /** Tells if this key is PRI key */
    virtual bool IsEchoKey() const { return true; }


    /** Get ECHO Key - two echo offset values */
    std::pair<int, int> GetEchoKey() const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
