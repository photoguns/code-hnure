#ifndef _BLOCKKEY_H_
#define _BLOCKKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "key.h"


/** C++ class for keys generation for block algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Mar 25th, 2009
*
*/
class BlockKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    BlockKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    virtual ~BlockKey();


    /** Tells if this key is Block key */
    virtual bool IsBlockKey() const { return true; }


    /** Get block key */
    std::vector<int> GetBlockKey( size_t _size ) const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
