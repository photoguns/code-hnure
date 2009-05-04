#ifndef POINT_H
#define POINT_H

#include "bignum.h"

// Point
struct Point
{
    BigNum x;
    BigNum y;

    // Constructor
    Point() {}
    Point(const BigNum& _x, const BigNum& _y)
    {
        x = _x;
        y = _y;
    }

    // Copy constructor
    Point( const Point& _rhs )
    {
        *this = _rhs;
    }

    // Operator=
    void operator=( const Point& _rhs )
    {
        x = _rhs.x;
        y = _rhs.y;
    }

    // Operator==
    bool operator==( const Point& _rhs ) const
    {
        return x == _rhs.x && y == _rhs.y;
    }
};

#endif