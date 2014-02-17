#include "rational.h"

Rational::Rational(int numerator, int denominator) :
    m_Numr(numerator), m_Denom(denominator)
{
    if (m_Denom == 0 || m_Denom == 1)
        return;
    if (m_Numr == 0)
    {
        m_Denom = 1;
        return;
    }
    if (m_Denom < 0)
    {
        m_Numr = -m_Numr;
        m_Denom = -m_Denom;
    }
    int gcd = (m_Numr < 0 ? -m_Numr : m_Numr);
    int denom = m_Denom;
    while (gcd != denom)
    {
        if (gcd > denom)
            gcd -= denom;
        else
            denom -= gcd;
    }
    if (gcd > 1)
    {
        m_Numr /= gcd;
        m_Denom /= gcd;
    }
}

Rational Rational::operator-() const
{
    return Rational(-m_Numr, m_Denom);
}

Rational Rational::operator+(const Rational& rhs) const
{
    return Rational(m_Numr * rhs.m_Denom + rhs.m_Numr * m_Denom, m_Denom * rhs.m_Denom);
}

Rational Rational::operator*(const Rational& rhs) const
{
    return Rational(m_Numr * rhs.m_Numr, m_Denom * rhs.m_Denom);
}

bool Rational::operator<(const Rational& rhs) const
{
    return (m_Numr * rhs.m_Denom < rhs.m_Numr * m_Denom);
}

bool Rational::operator==(const Rational& rhs) const
{
    return (m_Numr == rhs.m_Numr && m_Denom == rhs.m_Denom);
}
