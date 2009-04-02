#ifndef _PRIKEY_H_
#define _PRIKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "key.h"


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
    PRIKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    virtual ~PRIKey();


    /** Tells if this key is PRI key */
    virtual bool IsPRIKey() const { return true; }


    /** Get PRI Key of desired size */
    std::vector<int> GetPRIKey( size_t _size ) const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
