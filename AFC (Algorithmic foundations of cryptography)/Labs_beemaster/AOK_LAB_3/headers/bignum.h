#ifndef BIGNUM_H
#define BIGNUM_H

#include "mmath.h"

// M_LONG wrapper
struct BigNum
{
public:

    // M_LONG
    mutable M_LONG mlong;

    //Convert from BigNum to M_LONG
    operator M_LONG&() const { return mlong; }

    // Constructor
    BigNum(M_LONG init) { m_copy(mlong, init); }

    // Default constructor
    BigNum() {}

    // Operator=
    BigNum& operator=(const BigNum& rhs)
    {
        m_copy(mlong, rhs);
        return *this;
    }

    // Operator==
    bool operator==(const BigNum& rhs)
    {
        return !m_cmp(mlong, rhs);
    }
};

#endif