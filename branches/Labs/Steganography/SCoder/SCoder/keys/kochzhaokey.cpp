////////////////////////////////////////////////////////////////////////////////

#include <sstream>
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


std::vector<int> KochZhaoKey::GetKochZhaoKey( size_t _tableSize )
{
    // Get key hash
    std::string keyHash = GetKeyHash();

    size_t middle = _tableSize / 2;

    Coord first(middle, middle);
    Coord second(middle, middle);

    int number;

    std::stringstream stream;
    stream << std::hex << keyHash[0];
    stream >> number;
    first.first -= (number % 3) + 1;

    stream << std::hex << keyHash[1];
    stream >> number;
    first.second -= (number % 3) + 1;

    stream << std::hex << keyHash[1];
    stream >> number;
    first.second -= (number % 3) + 1;

    stream << std::hex << keyHash[1];
    stream >> number;
    first.second -= (number % 3) + 1;

    // Key hash length
    size_t hashLength = keyHash.length();

    // Key -- pair of two coordinates
    
    {
        // Next interval
        int number;

        // Convert char to integer
        

        // Add interval
        key.push_back(number);
    }

    return key;
}

