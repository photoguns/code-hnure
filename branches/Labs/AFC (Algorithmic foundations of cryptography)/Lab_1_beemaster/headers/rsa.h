/** (C) 2009 */

#ifndef _RSA_H_
#define _RSA_H_

////////////////////////////////////////////////////////////////////////////////

#include "primenumbersmanager.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for RSA encryption/decryption
*       Inverse numbers computation by chain fractions algorithm
*
*  @author  Roman Pasechnik
*  @since   March 4th, 2009
*  @updated March 9th, 2009
*
*/
class RSA
{

////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////

    /** Constructor */
    RSA ( unsigned long _keyLength );


    /** Destructor */
    ~RSA ();


    /** Generates public key, private key and module */
    void GenerateKeys ( mpz_class& _publicKey,
                        mpz_class& _privateKey,
                        mpz_class& _mod );


    /** Encrypts message */
    void Encrypt (       mpz_class& _encryptedMsg,
                   const mpz_class& _msg,
                   const mpz_class& _publicKey,
                   const mpz_class& _mod );


    /** Decrypts message */
    void Decrypt (       mpz_class& _msg,
                   const mpz_class& _encryptedMsg,
                   const mpz_class& _privateKey,
                   const mpz_class& _mod );


////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////


    /** Computes inverse number */
    int Inverse (        mpz_class& _invNum,
                   const mpz_class& _num,
                   const mpz_class& _mod );


////////////////////////////////////////////////////////////////////////////////


    /** Generates prime numbers for RSA */
    PrimeNumbersManager m_PrimeNumbersManager;


    /** RSA key length */
    unsigned long m_KeyLength;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_RSA_H_