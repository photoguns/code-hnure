#include <iostream>
#include <vector>
#include <cassert>

#include "bignum.h"
#include "PolynomsLib_Bin_1.h"


// Init polynom x with bits
void init_poly(BigNum& _poly, std::vector<int>& _bits);

// Array of elements for massive inversion
typedef std::vector<BigNum> Elements;

// Inverts all input elements modulo mod
void multy_inversion(const Elements& _input, Elements& _output, const BigNum& _mod);

// Pol
void mod_pol(BigNum& _poly, int m, int k);


int main()
{
    // Mod
    BigNum mod;

    std::vector<int> bits;
    bits.push_back(0);
    bits.push_back(6);
    bits.push_back(167);

    // Init mod. f(x) = x^167 + x^6 + 1
    init_poly(mod, bits);

    // Elements for multy inversion
    Elements input;
    BigNum number;
    const int numberLength = 5;

    // Generate random input
    for (int i = 0; i < 20; ++i)
    {
        m_rand(number, numberLength);
        input.push_back(number);
    }

    // Inverted elements
    Elements output(input.size());
    multy_inversion(input, output, mod);

    // Multy inversion test
    BigNum check;
    for (size_t i = 1; i < input.size(); ++i)
    {
        inv_pol(input[i], mod, check);
        assert( output[i] == check );
    }



    // Generate random input for mod_pol
    for (int i = 0; i < 20; ++i)
    {
        BigNum a, b;

        m_rand(a, 11);
        b = a;
        mod_pol(a, 167, 6);
        rem_pol(b, mod);
        assert( a == b );
    }



    return 0;
}

void init_poly(BigNum& _poly, std::vector<int>& _bits)
{
    memset( _poly, 0, sizeof(_poly) );
    _poly[0] = _bits.back() / 32 + ((_bits.back() % 32) ? 1 : 0);
    for (size_t i = 0; i < _bits.size(); ++i)
        m_setbit(_poly, _bits[i]);
}

void multy_inversion(const Elements& _input, Elements& _output, const BigNum& _mod)
{
    // Element multiplies. Last element is a multiple of all elements
    Elements multiplies;
    multiplies.push_back(_input[0]);

    // Current multiply
    BigNum multiply;
    for (size_t i = 1; i < _input.size(); ++i)
    {
        mulmod_pol(multiplies[i - 1], _input[i], _mod, multiply);
        multiplies.push_back(multiply);
    }

    // Multiple inversion (inversion of elements multiply)
    BigNum inversion;
    inv_pol(multiplies.back(), _mod, inversion);

    BigNum inversionCopy;
    for (size_t i = _input.size() - 1; i > 0; --i)
    {
        mulmod_pol(inversion, multiplies[i - 1], _mod, _output[i]);
        mulmod_pol(inversion, _input[i], _mod, inversionCopy);
        inversion = inversionCopy;
    }
    _output[0] = inversion;
}


void mod_pol(BigNum& _poly, int m, int k)
{
    BigNum result;
    memset(result, 0, sizeof(result));

    for (int i = 2*m - 1; i >= m; --i)
    {
        if ( m_getbit(_poly, i - m) ^ m_getbit(_poly, i) )
            m_setbit(result, i - m);
        if ( m_getbit(_poly, i - m + k) ^ m_getbit(_poly, i) )
            m_setbit(result, i - m + k);
    }
    result[0] = _poly[0] % (m / 32 + ((m % 32) ? 1 : 0) );
    _poly = result;
}