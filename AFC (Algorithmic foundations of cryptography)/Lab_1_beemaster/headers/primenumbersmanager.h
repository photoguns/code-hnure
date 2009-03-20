/** (C) 2009 */

#ifndef _PRIMENUMBERSMANAGER_H_
#define _PRIMENUMBERSMANAGER_H_

////////////////////////////////////////////////////////////////////////////////

#include "gmpwrapper.h"

////////////////////////////////////////////////////////////////////////////////

/** C++ class for work with prime numbers
*    Prime numbers are checked by Miller-Rabin algorithm
*
*  @author  Roman Pasechnik
*  @since   March 4th, 2009
*  @updated March 20th, 2009
*
*/
class PrimeNumbersManager
{

////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////


    /** Constructor */
    PrimeNumbersManager ( unsigned long _rounds );


    /** Destructor */
    ~PrimeNumbersManager ();


    /** Generates prime number in the range 0 to _mod - 1, inclusive. */
    void GeneratePrime ( mpz_class& _num, const mpz_class& _mod );


    /** Generates prime number in the range 0 to 2^_length - 1, inclusive. */
    void GeneratePrime ( mpz_class& _num, unsigned long _length );


    /** Checks if number is prime using Miller-Rabin algorithm */
    bool IsPrime ( const mpz_class& _num );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /* Checks if _num is divisible by any of small primes, and saves quotient */
    bool IsDivisibleBySmallPrime ( mpz_class& _quotient,
                                   const mpz_class& _num );


////////////////////////////////////////////////////////////////////////////////


    /** Number of rounds in Miller-Rabin algorithm */
    const unsigned long m_Rounds;


    /** Random numbers generator */
    gmp_randclass m_RndGenerator;

    
    /** Prime numbers from 2 to 65521 */
    static const unsigned long m_SmallPrimes[];


////////////////////////////////////////////////////////////////////////////////
};

#endif //_PRIMENUMBERSMANAGER_H_
