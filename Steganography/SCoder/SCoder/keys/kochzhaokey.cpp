////////////////////////////////////////////////////////////////////////////////

#include "kochzhaokey.h"

////////////////////////////////////////////////////////////////////////////////


KochZhaoKey::KochZhaoKey( const std::string& _string, Key::KeyType _type )
:Key(_string, _type)
{
}


////////////////////////////////////////////////////////////////////////////////


KochZhaoKey::~KochZhaoKey()
{
}


////////////////////////////////////////////////////////////////////////////////


KochZhaoKey::TwoCoords KochZhaoKey::GetKochZhaoKey( size_t _tableSize ) const
{
    // Get key hash
    std::string keyHash = GetKeyHash();

    size_t middle = _tableSize / 2;

    // Key -- pair of two coordinates
    Coord first(middle, middle);
    Coord second(middle, middle);

    // Just modify coordinates slightly
    first.first -= (keyHash[0] % 2);
    first.second -= (keyHash[1] % 2);
    second.first += (keyHash[2] % 2) + 1;
    second.second += (keyHash[3] % 2) + 1;

    return std::make_pair(first, second);
}

