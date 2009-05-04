#include "point.h"
#include "PolynomsLib_Bin_1.H"

// Infinity point
M_LONG ZERO_M_LONG = {1, 0};
BigNum ZERO = ZERO_M_LONG;
Point I(ZERO, ZERO);


// Add two points
Point add ( const Point& P, const Point& Q, const BigNum& a, const BigNum& mod )
{
    // 1
    if (P == I)
    {
        return Q;
    }
    // 2
    if (Q == I)
    {
        return P;
    }

    // 3
    BigNum lambda, temp, invX;
    Point result;
    if (P.x != Q.x)
    {
        // 3.1
        if (P.y == Q.y || (P.x == ZERO) )
        {
            return I;
        }
        // 3.2

        // x^-1
        inv_pol(P.x, mod, invX);

        // y/x
        mulmod_pol(invX, P.y, mod, temp);

        // x1 + y/x
        add_pol(temp, P.x, lambda);

        // lambda^2
        BigNum lambda2;
        sqrmod_pol(lambda, mod, lambda2);

        // lambda^2 + lambda
        add_pol(lambda, lambda2, temp);

        // x3 = lambda^2 + lambda + a
        add_pol(temp, a, result.x);
    }
    else
    {
        // 4.1

        // x1 + x2
        add_pol(P.x, Q.x, temp);

        // (x1 + x2)^-1
        inv_pol(temp, mod, invX);

        // y1 + y2
        add_pol(P.y, Q.y, temp);

        // lambda = (y1 + y2) / (x1 + x2) mod f(t)
        mulmod_pol(temp, invX, mod, lambda);

        // 4.2
        BigNum lambda2;

        // lambda^2
        sqrmod_pol(lambda, mod, lambda2);

        // lambda + lambda^2
        add_pol(lambda, lambda2, temp);

        // lambda + lambda^2 + x1
        m_add(temp, P.x, invX);

        // lambda + lambda^2 + x1 + x2
        add_pol(invX, Q.x, temp);

        // x3 = lambda + lambda^2 + x1 + x2 + a;
        add_pol(temp, a, result.x);
    }

    // 5

    // x1 + x3
    add_pol(result.x, P.x, temp);

    // (x1 + x3)*lambda
    mulmod_pol(temp, lambda, mod, invX);
    
    // (x1 + x3)*lambda + x3
    add_pol(invX, result.x, temp);

    // y3 = (x1 + x3)*lambda + x3 + y2
    add_pol(temp, P.y, result.y);

    return result;
}

int main()
{
    // Curve parameters
    M_LONG mod = {1, 0x13};
    M_LONG a = {1, 1};
    
    // Point #1
    M_LONG x1 = {1, 2};
    M_LONG y1 = {1, 0xF};
    Point P(x1, y1);
    
    // Point #2
    M_LONG x2 = {1, 2};
    M_LONG y2 = {1, 0xD};
    Point Q(x2, y2);

    // Point #3 = Point #1 + Point #2
    Point R = add(P, Q, a, mod);

    return 0;
}