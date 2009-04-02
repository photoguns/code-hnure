#ifndef _BLOCKKEY_H_
#define _BLOCKKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "key.h"


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
    BlockKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    virtual ~BlockKey();


    /** Tells if this key is Block key */
    virtual bool IsBlockKey() const { return true; }


    ///** Utility type: Point with two coordinates */
    //typedef std::pair<int, int> Point;


    ///** Utility type: Block of points */
    //typedef std::vector<Point>  Block;


    ///** Utility type: Array of Blocks */
    //typedef std::vector<Block> Blocks;


    ///** Get block key */
    //Blocks GetBlockKey( int _sizeX, int _sizeY ) const;


    /** Get block key */
    std::vector<int> GetBlockKey( size_t _size ) const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
