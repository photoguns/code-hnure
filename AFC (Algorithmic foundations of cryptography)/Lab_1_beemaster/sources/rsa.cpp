/** (C) 2009 */

////////////////////////////////////////////////////////////////////////////////

#include "rsa.h"
#include <stack>

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
    mpz_powm( _encryptedMsg.get_mpz_t(), _msg.get_mpz_t(), _publicKey.get_mpz_t(), _mod.get_mpz_t() );
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
