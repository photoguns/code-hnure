/** (C) 2009 */

////////////////////////////////////////////////////////////////////////////////

#include "primenumbersmanager.h"

////////////////////////////////////////////////////////////////////////////////


const unsigned long PrimeNumbersManager::m_SmallPrimes[] = {
#include "smallprimes" //LOL
};


////////////////////////////////////////////////////////////////////////////////


PrimeNumbersManager::PrimeNumbersManager( unsigned long _rounds )
: m_Rounds(_rounds)
{
    // Initialize state for a Mersenne Twister algorithm.
    // This algorithm is fast and has good randomness properties.
    gmp_randinit_default(m_State);
}


////////////////////////////////////////////////////////////////////////////////


PrimeNumbersManager::~PrimeNumbersManager()
{
}


////////////////////////////////////////////////////////////////////////////////


void PrimeNumbersManager::GeneratePrime ( mpz_class& _num, const mpz_class& _mod )
{
    do
    {
        // Generate random number
        GenerateRandom(_num, _mod);
    }
    // Until we get the prime one
    while ( !IsPrime(_num) );
}


////////////////////////////////////////////////////////////////////////////////


void PrimeNumbersManager::GeneratePrime ( mpz_class& _num, unsigned long _length )
{
    do
    {
        // Generate random number
        GenerateRandom(_num, _length);
    }
    // Until we get the prime one
    while ( !IsPrime(_num) );
}


////////////////////////////////////////////////////////////////////////////////


void PrimeNumbersManager::GenerateRandom( mpz_class& _num, const mpz_class& _mod )
{
    // Generate a uniform random integer in the range 0 to _mod - 1, inclusive.
    mpz_urandomm(_num.get_mpz_t(), m_State, _mod.get_mpz_t());
}


////////////////////////////////////////////////////////////////////////////////


void PrimeNumbersManager::GenerateRandom( mpz_class& _num, unsigned long _length )
{
    // Generate a uniformly distributed random integer in the range 0 to 2^_length - 1, inclusive.
    mpz_urandomb(_num.get_mpz_t(), m_State, _length);
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
    while ( mpz_divisible_2exp_p(numWithoutOne.get_mpz_t(), powerOfTwo + 1) )
        powerOfTwo++;

    mpz_tdiv_q_2exp(quotient.get_mpz_t(), numWithoutOne.get_mpz_t(), powerOfTwo);

    for (unsigned long i = 0; i < m_Rounds; ++i)
    {
        // Generate random: 1 < witnessOfPrime < _num
        mpz_class rnd;
        GenerateRandom(rnd, _num);
        if (rnd == 0)
            ++rnd;

        // Calculate poweredRnd = rnd^quotient(mod _number)
        mpz_class poweredRnd;
        mpz_powm ( poweredRnd.get_mpz_t(),
                   rnd.get_mpz_t(),
                   quotient.get_mpz_t(),
                   _num.get_mpz_t() );

        // Check if rnd is a witness of prime of _number
        if ( poweredRnd !=  1 && poweredRnd != numWithoutOne )
        {
            bool rndIsAWitnessOfPrime = false;
            for (unsigned long j = 1; j < powerOfTwo; j++)
            {
                // poweredRnd ^= 2 (mod _num)
                mpz_powm_ui ( poweredRnd.get_mpz_t(),
                              poweredRnd.get_mpz_t(),
                              2,
                              _num.get_mpz_t() );

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


bool PrimeNumbersManager::IsDivisibleBySmallPrime( mpz_class& _quotient, const mpz_class& _num )
{
    for ( int i = 0; i < sizeof(m_SmallPrimes) / sizeof (unsigned long); ++i )
    {
        if ( mpz_divisible_ui_p( _num.get_mpz_t(), m_SmallPrimes[i] ) )
        {
            mpz_divexact_ui( _quotient.get_mpz_t(), _num.get_mpz_t(), m_SmallPrimes[i] );
            return true;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
