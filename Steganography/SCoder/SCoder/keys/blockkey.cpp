////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include "blockkey.h"

////////////////////////////////////////////////////////////////////////////////


BlockKey::BlockKey( const std::string& _string, Key::KeyType _type )
:Key(_string, _type)
{
}


////////////////////////////////////////////////////////////////////////////////


BlockKey::~BlockKey()
{
}


////////////////////////////////////////////////////////////////////////////////


std::vector<int> BlockKey::GetBlockKey( size_t _size ) const
{
    // Get key hash
    std::string keyHash = GetKeyHash();

    // Key hash length
    size_t hashLength = keyHash.length();

    // Key -- array of integers (intervals)
    std::vector<int> key;

    // Generate key of desired length
    for (size_t i = 0; i < _size; ++i)
    {
        // Next interval
        int number;

        // Convert char to integer
        std::stringstream stream;
        stream << std::hex << keyHash[i % hashLength] + 1;
        stream >> number;

        // Add interval
        key.push_back(number);
    }

    return key;
}


////////////////////////////////////////////////////////////////////////////////
