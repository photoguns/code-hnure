////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include "quantkey.h"


////////////////////////////////////////////////////////////////////////////////


QuantKey::QuantKey( const std::string& _string, Key::KeyType _type )
:Key(_string, _type)
{
}


////////////////////////////////////////////////////////////////////////////////


QuantKey::~QuantKey()
{
}


////////////////////////////////////////////////////////////////////////////////


std::bitset<QuantKey::quantizationTableSize> QuantKey::GetQuantKey() const
{
    // Get key hash
    std::string keyHash = GetKeyHash();

    // Key hash length
    size_t hashLength = keyHash.length();

    // Key -- array of integers (intervals)
    std::bitset<quantizationTableSize> key;

    // Generate key of quantizationTableSize length
    for (size_t i = 0; i < key.size(); ++i)
    {
        // Next value in key
        int number;

        // Convert char to integer
        std::stringstream stream;
        stream << std::hex << keyHash[i % hashLength];
        stream >> number;

        // Add bit
        key[i] = number % 2 > 0;
    }

    return key;
}


////////////////////////////////////////////////////////////////////////////////
