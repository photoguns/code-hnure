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


//BlockKey::Blocks BlockKey::GetBlockKey( int _sizeX, int _sizeY ) const
//{
//    // Get key hash
//    std::string keyHash = GetKeyHash();
//
//    // Hash length
//    size_t hashLength = keyHash.length();
//
//    // Number of points in a block
//    size_t pointsCounter = 0;
//
//    // Key - blocks of points
//    Blocks key;
//
//    // Generate key for area _sizeX * _sizeY
//    for (int i = 0; i < _sizeX; ++i)
//        for (int j = 0; j < _sizeY; ++j)
//        {
//            if (pointsCounter == 0)
//            {
//                // Start new Block
//                key.push_back( Block() );
//
//                // Convert char to integer - number of points in a block
//                std::stringstream stream;
//                stream << std::hex << keyHash[(i * _sizeY + j) % hashLength];
//                stream >> pointsCounter;
//            }
//            else
//            {
//                // Decrement number of points left to put in current block
//                --pointsCounter;
//
//                // Put point in a block
//                key.back().push_back( std::make_pair(i,j) );
//            }
//        }
//
//    return key;
//}


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
        stream << std::hex << keyHash[i % hashLength];
        stream >> number;

        // Add interval
        key.push_back(number);
    }

    return key;
}


////////////////////////////////////////////////////////////////////////////////
