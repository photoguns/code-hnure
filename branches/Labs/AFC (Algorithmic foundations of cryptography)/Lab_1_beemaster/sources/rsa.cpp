/** (C) 2009 */

////////////////////////////////////////////////////////////////////////////////

#include "rsa.h"
#include <vector>
#include "math.h"

////////////////////////////////////////////////////////////////////////////////


RSA::RSA ( unsigned long _keyLength )
: m_PrimeNumbersManager( _keyLength ), m_KeyLength( _keyLength )
{
}


////////////////////////////////////////////////////////////////////////////////


RSA::~RSA ()
{
}


////////////////////////////////////////////////////////////////////////////////


void RSA::GenerateKeys( mpz_class& _publicKey, mpz_class& _privateKey, mpz_class& _mod )
{
    // Generate prime numbers P and Q
    mpz_class P, Q;
    m_PrimeNumbersManager.GeneratePrime( P, m_KeyLength );
    m_PrimeNumbersManager.GeneratePrime( Q, m_KeyLength );
    _mod = P * Q;

    // Euler's function EF(_mod) */
    const mpz_class EF = ( P - 1 ) * ( Q - 1 );

    do
    {
        // Generate random number
        m_PrimeNumbersManager.GeneratePrime(_publicKey, EF);
    }
    // Until it has an inverse number
    while ( !Inverse(_privateKey, _publicKey, EF) );
}


////////////////////////////////////////////////////////////////////////////////


void RSA::Encrypt( mpz_class& _encryptedMsg, const mpz_class& _msg, const mpz_class& _publicKey, const mpz_class& _mod )
{
    // Encrypt message: _encryptedMsg = _msg ^ _publicKey ( mod _mod )
    BlockPowering(_encryptedMsg, _msg, _publicKey, _mod);
}


////////////////////////////////////////////////////////////////////////////////


void RSA::Decrypt( mpz_class& _msg, const mpz_class& _encryptedMsg, const mpz_class& _privateKey, const mpz_class& _mod )
{
    // Decrypt message: _msg = _encryptedMsg ^ _privateKey ( mod _mod )
    mpz_powm( _msg.get_mpz_t(), _encryptedMsg.get_mpz_t(), _privateKey.get_mpz_t(), _mod.get_mpz_t() );
}


////////////////////////////////////////////////////////////////////////////////


int RSA::Inverse( mpz_class& _invNum, const mpz_class& _num, const mpz_class& _mod )
{
    // Compute the inverse of _num modulo _mod and put the result in _invNum.
    // If the inverse exists, the return value is non-zero and _invNum will satisfy 0 <= _invNum < _mod.
    // If an inverse doesn’t exist the return value is zero and _invNum is undefined.

    // return mpz_invert( _invNum.get_mpz_t(), _num.get_mpz_t(), _mod.get_mpz_t() );

    // _mod * Y + _num * _invNum = 1. Calculate _invNum
    // _mod > _num
    // ( _mod, _num ) = 1

    // a
    mpz_class divisible = _mod;
    // b
    mpz_class divisor = _num;
    // r0
    mpz_class quotient;
    // s0
    mpz_class remainder;
    // a_n-1, a_n-2
    mpz_class invNum_1, invNum_2;

    int counter = 0;
    while ( true )
    {
        // divisible / divisor = quotient + remainder / divisor
        mpz_fdiv_qr( quotient.get_mpz_t(),
                     remainder.get_mpz_t(),
                     divisible.get_mpz_t(),
                     divisor.get_mpz_t() );

        if (remainder == 0)
            // Exit
            return counter;
        else
        {
            switch (counter)
            {
            case 0:
                // a0 = r0
                _invNum = quotient;
        	    break;
            case 1:
                // a1 = r1*r0 + 1
                _invNum = quotient * _invNum + 1;
                invNum_1 = 1;
                break;
            default:
                invNum_2 = invNum_1;
                invNum_1 = _invNum;
                // a_n = r_n * a_n-1 + a_n-2
                _invNum = quotient * invNum_1 + invNum_2;
                break;
            }

            // Next round
            divisible = divisor;
            divisor = remainder;

            ++counter;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////


void RSA::BlockPowering( mpz_class& _result, const mpz_class& _base, const mpz_class& _exp, const mpz_class& _mod )
{
    // w
    const unsigned long blockLength = 3;

    // t
    const unsigned long sizeInBase = mpz_sizeinbase(_exp.get_mpz_t(), 2);

    const unsigned long expTableSize =   sizeInBase / blockLength + 
                                       ( sizeInBase % blockLength ? 1 : 0 );

    typedef std::vector<unsigned long> ULVec;
    // d[]
    ULVec expTable(expTableSize);

    // 2^w
    const unsigned long twoPowW = Pow(2, blockLength);

    // 2^(i*w)
    mpz_class twoPowIPowW;
    mpz_powm_ui ( twoPowIPowW.get_mpz_t(),
                  mpz_class(twoPowW).get_mpz_t(),
                  sizeInBase / blockLength,
                  _mod.get_mpz_t() );

    // Fetch expTable (calculate elements of the expression)
    // e.g. _exp = expTable[2] * 2^8 + expTable[1] * 2^4 + expTable[0] * 1
    mpz_class quotient;
    mpz_class remainder = _exp;
    for ( ULVec::reverse_iterator rit = expTable.rbegin();
                                  rit != expTable.rend();
                                  ++rit )
    {
        quotient = remainder / twoPowIPowW;
        *rit = quotient.get_ui();
        remainder %= twoPowIPowW;
        twoPowIPowW /= twoPowW;
    }

    typedef std::vector<mpz_class> MPZVec;
    // x[]
    MPZVec baseTable(twoPowW);
    for (unsigned long i = 0; i < baseTable.size(); ++i)
    {
        // x^0, x^1, ... ,x^(2w-1)
        mpz_powm_ui ( baseTable[i].get_mpz_t(),
                     _base.get_mpz_t(),
                     i,
                     _mod.get_mpz_t() );
    }

    // Clear result
    _result = 1;

    for (long i = expTableSize - 1; i >= 0; --i)
    {
        for (unsigned long j = 0; j < blockLength; ++j)
        {
            // y = y^2 (mod n)
            mpz_powm_ui ( _result.get_mpz_t(),
                          _result.get_mpz_t(),
                          2,
                          _mod.get_mpz_t() );
        }
        // k = d[i]
        unsigned long k = expTable[i];
        // y = y * x[k] (mod n)
        _result = ( _result * baseTable[k] ) % _mod;
    }
}


////////////////////////////////////////////////////////////////////////////////


unsigned long RSA::Pow( unsigned long _base, unsigned long _exp ) const
{
    return static_cast<unsigned long>(
        pow ( static_cast<double>(_base), static_cast<int>(_exp) )
                                     );
}


////////////////////////////////////////////////////////////////////////////////
