////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include "prikey.h"


////////////////////////////////////////////////////////////////////////////////


PRIKey::PRIKey( const std::string& _string, Key::KeyType _type )
:Key(_string, _type)
{
}


////////////////////////////////////////////////////////////////////////////////


PRIKey::~PRIKey()
{
}


////////////////////////////////////////////////////////////////////////////////


std::vector<int> PRIKey::GetPRIKey( size_t _size ) const
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
        stream << std::hex << keyHash[i % hashLength];
        stream >> number;

        // Add interval
        key.push_back(number);
    }
    
    return key;
}

