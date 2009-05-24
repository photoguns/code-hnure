#ifndef _KOCHZHAOKEY_H_
#define _KOCHZHAOKEY_H_

////////////////////////////////////////////////////////////////////////////////

#include <utility>
#include "key.h"


/** C++ class for keys generation for Koch-Zhao algorithm
*
*
*  @author  Roman Pasechnik
*  @since   Mar 25th, 2009
*  @updated Mar 25th, 2009
*
*/
class KochZhaoKey : public Key
{
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    KochZhaoKey( const std::string& _string, Key::KeyType _type );


    /** Destructor */
    virtual ~KochZhaoKey();


    /** Tells if this key is PRI key */
    virtual bool IsKochZhaoKey() const { return true; }


    /** Utility type: coordinate of a point in a table */
    typedef std::pair<int, int> Coord;


    /** Get Koch-Zhao Key for square table with _tableSize side */
    std::pair<Coord, Coord> GetKochZhaoKey( size_t _tableSize ) const;


////////////////////////////////////////////////////////////////////////////////
};

#endif
