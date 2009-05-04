/** (C) 2009 */

#ifndef _RSA_H_
#define _RSA_H_

////////////////////////////////////////////////////////////////////////////////

#include "primenumbersmanager.h"

////////////////////////////////////////////////////////////////////////////////


/** C++ class for RSA encryption/decryption
*       Inverse numbers computation by chain fractions algorithm
*       Exponentiation by block method
*
*  @author  Roman Pasechnik
*  @since   March 4th, 2009
*  @updated March 15th, 2009
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


    /** Computes _base ^ _exp ( mod _mod ) */
    void BlockPowering (       mpz_class& _result,
                         const mpz_class& _base,
                         const mpz_class& _exp,
                         const mpz_class& _mod );


    /** Computes _base ^ _exp */
    unsigned long pow ( unsigned long _base, unsigned long _exp ) const;


////////////////////////////////////////////////////////////////////////////////


    /** Generates prime numbers for RSA */
    PrimeNumbersManager m_PrimeNumbersManager;


    /** RSA key length */
    unsigned long m_KeyLength;


////////////////////////////////////////////////////////////////////////////////
};

#endif //_RSA_H_