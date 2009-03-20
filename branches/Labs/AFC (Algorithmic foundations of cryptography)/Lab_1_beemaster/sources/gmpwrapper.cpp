#include "gmpwrapper.h"


////////////////////////////////////////////////////////////////////////////////

unsigned long mpz_sizeinbase ( const mpz_class& _num, int _base )
{
    return mpz_sizeinbase ( _num.get_mpz_t(), _base );
}

////////////////////////////////////////////////////////////////////////////////

int mpz_divisible_2exp_p ( const mpz_class& _num, unsigned long _exp )
{
    return mpz_divisible_2exp_p ( _num.get_mpz_t(), _exp );
}

////////////////////////////////////////////////////////////////////////////////

int mpz_divisible_ui_p ( const mpz_class& _num, unsigned long _divisor )
{
    return mpz_divisible_ui_p ( _num.get_mpz_t(), _divisor );
}

////////////////////////////////////////////////////////////////////////////////

void mpz_divexact_ui ( mpz_class& _quotient, const mpz_class& _divisible,
                       unsigned long _divisor )
{
    mpz_divexact_ui ( _quotient.get_mpz_t(), _divisible.get_mpz_t(), _divisor );
}

////////////////////////////////////////////////////////////////////////////////

void mpz_fdiv_q_2exp ( mpz_class& _qoutient, const mpz_class& _divisible,
                       unsigned long _exp )
{
    mpz_fdiv_q_2exp ( _qoutient.get_mpz_t(), _divisible.get_mpz_t(), _exp );
}

////////////////////////////////////////////////////////////////////////////////

void mpz_fdiv_qr ( mpz_class& _qoutient, mpz_class& _remainder,
                   const mpz_class& _divisible, const mpz_class& _divisor )
{
    mpz_fdiv_qr ( _qoutient.get_mpz_t(), _remainder.get_mpz_t(),
                  _divisible.get_mpz_t(), _divisor.get_mpz_t() );
}

////////////////////////////////////////////////////////////////////////////////

void mpz_powm ( mpz_class& _result, const mpz_class& _base,
                const mpz_class& _exp, const mpz_class& _mod )
{
    mpz_powm ( _result.get_mpz_t(), _base.get_mpz_t(),
               _exp.get_mpz_t(), _mod.get_mpz_t() );
}

////////////////////////////////////////////////////////////////////////////////

void mpz_powm_ui ( mpz_class& _result, const mpz_class& _base,
                   unsigned long _exp, const mpz_class& _mod )
{
    mpz_powm_ui ( _result.get_mpz_t(), _base.get_mpz_t(),
                  _exp, _mod.get_mpz_t() );
}

////////////////////////////////////////////////////////////////////////////////

int mpz_invert ( mpz_class& _invNum, const mpz_class& _num,
                 const mpz_class& _mod )
{
    return mpz_invert ( _invNum.get_mpz_t(), _num.get_mpz_t(),
                        _mod.get_mpz_t() );
}

////////////////////////////////////////////////////////////////////////////////

int mpz_tstbit ( const mpz_class& _num, unsigned long int _bitNumber )
{
    return mpz_tstbit (_num.get_mpz_t(), _bitNumber );
}

////////////////////////////////////////////////////////////////////////////////