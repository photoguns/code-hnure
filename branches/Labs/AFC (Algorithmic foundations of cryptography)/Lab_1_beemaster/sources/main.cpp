/** (C) 2009 */

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include "gmpwrapper.h"
#include "primenumbersmanager.h"
#include "rsa.h"

////////////////////////////////////////////////////////////////////////////////

/** An example of using GMP library,
*   RSA and PrimeNumbersManager classes
*
*  @author  Roman Pasechnik
*  @since   March 4th, 2009
*  @updated March 20th, 2009
*
*/
int main ()
{
    // Two long numbers
    const mpz_class P ("0x9df3ef1d39b8708c11a20acc5d45c7\
                       fccc61f6d231fe7bd370cd54cea9bd6e9\
                       ba4dba9147f6e28539551dc2cb09152ec\
                       7249bb52ffbc3bccedb374f56f18544d");
    const mpz_class Q ("0xf5fe50db5ae28905a234ee79b4a229\
                       2152e68e5ec2e3603dba0262f88bcca0b\
                       190ca7e6cd79b004c10555a11b51fbad0\
                       790f53f3f440ab728e352852ab74d85d");
    
    // Print them
    std::cout << "P = " << P.get_str() << std::endl
              << "Q = " << Q.get_str() << std::endl;
 
    // Number of rounds in Miller-Rabin test
    const unsigned long rounds = 111;

    // Create prime numbers manager
    PrimeNumbersManager primeManager(rounds);

    // Check if numbers are prime or composite
    std::cout << "P is "<< ( primeManager.IsPrime(P) ?
                             "prime" : "composite" ) << std::endl
              << "Q is "<< ( primeManager.IsPrime(Q) ?
                             "prime" : "composite" ) << std::endl;

    // Create RSA encrypter / decrypter
    RSA rsa(rounds);

    // Generate pair of public and private key
    mpz_class publicKey, privateKey, mod;
    rsa.GenerateKeys(publicKey, privateKey, mod);

    // Original message
    mpz_class message("0xCAFEBABE1111DEADBEEF");

    // Encrypt message
    mpz_class encryptedMsg;
    rsa.Encrypt(encryptedMsg, message, publicKey, mod);

    // Decrypt encrypted message
    mpz_class decryptedMsg;
    rsa.Decrypt(decryptedMsg, encryptedMsg, privateKey, mod);

    // Check
    assert(decryptedMsg == message);

    // Exit
    return 0;
}
