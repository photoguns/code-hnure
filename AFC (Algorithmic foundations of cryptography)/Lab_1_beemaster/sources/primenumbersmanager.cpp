/** (C) 2009 */

////////////////////////////////////////////////////////////////////////////////

#include "primenumbersmanager.h"

////////////////////////////////////////////////////////////////////////////////


const unsigned long PrimeNumbersManager::m_SmallPrimes[] = {
#include "smallprimes" //LOL
};


////////////////////////////////////////////////////////////////////////////////


PrimeNumbersManager::PrimeNumbersManager ( unsigned long _rounds )
: m_Rounds(_rounds), m_RndGenerator(gmp_randinit_default)
{
}


////////////////////////////////////////////////////////////////////////////////


PrimeNumbersManager::~PrimeNumbersManager()
{
}


////////////////////////////////////////////////////////////////////////////////


void PrimeNumbersManager::GeneratePrime ( mpz_class& _num,
                                          const mpz_class& _mod )
{
    do
    {
        // Generate a uniform random integer in the range
        // 0 to _mod - 1, inclusive.
        _num = m_RndGenerator.get_z_range(_mod);
    }
    // Until we get the prime one
    while ( !IsPrime(_num) );
}


////////////////////////////////////////////////////////////////////////////////


void PrimeNumbersManager::GeneratePrime ( mpz_class& _num,
                                          unsigned long _length )
{
    do
    {
        // Generate a uniformly distributed random integer in the range
        // 0 to 2^_length - 1, inclusive.
        _num = m_RndGenerator.get_z_bits(_length);
    }
    // Until we get the prime one
    while ( !IsPrime(_num) );
}


////////////////////////////////////////////////////////////////////////////////


bool PrimeNumbersManager::IsPrime ( const mpz_class& _num )
{
    // 0 and 1 are not primes
    if (_num == 0 || _num == 1)
        return false;

    // Check divisibility by small primes first
    mpz_class quotient;
    if ( IsDivisibleBySmallPrime(quotient, _num) )
        return quotient == 1;

    // Calculate number - 1
    mpz_class numWithoutOne = _num - 1;

    // Calculate counter and quotient, number - 1 = 2^counter * quotient
    unsigned long powerOfTwo = 0;
    while ( mpz_divisible_2exp_p(numWithoutOne, powerOfTwo + 1) )
        powerOfTwo++;

    mpz_fdiv_q_2exp(quotient, numWithoutOne, powerOfTwo);

    for (unsigned long i = 0; i < m_Rounds; ++i)
    {
        // Generate random: 1 < witnessOfPrime < _num
        mpz_class rnd;
        rnd = m_RndGenerator.get_z_range(_num);
        if (rnd == 0)
            ++rnd;

        // Calculate poweredRnd = rnd^quotient(mod _number)
        mpz_class poweredRnd;
        mpz_powm ( poweredRnd, rnd, quotient, _num );

        // Check if rnd is a witness of prime of _number
        if ( poweredRnd !=  1 && poweredRnd != numWithoutOne )
        {
            bool rndIsAWitnessOfPrime = false;
            for (unsigned long j = 1; j < powerOfTwo; j++)
            {
                // poweredRnd ^= 2 (mod _num)
                mpz_powm_ui ( poweredRnd, poweredRnd, 2, _num );

                if ( poweredRnd == numWithoutOne )
                {
                    rndIsAWitnessOfPrime = true;
                    break;
                }
            }
            // rnd is not a witness of prime
            // _num is composite
            if (!rndIsAWitnessOfPrime)
                return false;
        }
    }
    
    // All generated random numbers were witnesses of prime
    // so _num is probably prime
    return true;
}


////////////////////////////////////////////////////////////////////////////////


bool PrimeNumbersManager::IsDivisibleBySmallPrime ( mpz_class& _quotient,
                                                    const mpz_class& _num )
{
    for ( int i = 0; i < sizeof(m_SmallPrimes) / sizeof (unsigned long); ++i )
    {
        if ( mpz_divisible_ui_p( _num, m_SmallPrimes[i] ) )
        {
            mpz_divexact_ui( _quotient, _num, m_SmallPrimes[i] );
            return true;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
