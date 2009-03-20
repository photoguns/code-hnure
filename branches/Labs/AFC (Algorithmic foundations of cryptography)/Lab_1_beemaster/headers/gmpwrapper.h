#ifndef __GMPWRAPPER_H_
#define __GMPWRAPPER_H_

////////////////////////////////////////////////////////////////////////////////

#include "gmpxx.h"

////////////////////////////////////////////////////////////////////////////////

/* C++ wrapper for GMP functions
*
*  @author  Roman Pasechnik
*  @since   March 19th, 2009
*  @updated March 20th, 2009
*
*/

////////////////////////////////////////////////////////////////////////////////

unsigned long mpz_sizeinbase ( const mpz_class& _num, int _base );

////////////////////////////////////////////////////////////////////////////////

int mpz_divisible_2exp_p ( const mpz_class& _num, unsigned long _exp );

////////////////////////////////////////////////////////////////////////////////

int mpz_divisible_ui_p ( const mpz_class& _num, unsigned long _divisor );

////////////////////////////////////////////////////////////////////////////////

void mpz_divexact_ui ( mpz_class& _quotient, const mpz_class& _divisible,
                       unsigned long _divisor );

////////////////////////////////////////////////////////////////////////////////

void mpz_fdiv_q_2exp ( mpz_class& _qoutient, const mpz_class& _divisible,
                       unsigned long _exp );

////////////////////////////////////////////////////////////////////////////////

void mpz_fdiv_qr ( mpz_class& _qoutient, mpz_class& _remainder,
                   const mpz_class& _divisible, const mpz_class& _divisor );

////////////////////////////////////////////////////////////////////////////////

void mpz_powm ( mpz_class& _result, const mpz_class& _base,
                const mpz_class& _exp, const mpz_class& _mod );

////////////////////////////////////////////////////////////////////////////////

void mpz_powm_ui ( mpz_class& _result, const mpz_class& _base,
                   unsigned long _exp, const mpz_class& _mod );

////////////////////////////////////////////////////////////////////////////////

int mpz_invert ( mpz_class& _invNum, const mpz_class& _num,
                 const mpz_class& _mod );

////////////////////////////////////////////////////////////////////////////////

int mpz_tstbit ( const mpz_class& _num, unsigned long int _bitNumber );

////////////////////////////////////////////////////////////////////////////////

#endif