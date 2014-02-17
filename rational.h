#ifndef RATIONAL_H
#define RATIONAL_H


class Rational
{
    public:
        Rational(int numerator, int denominator = 1);

        Rational operator-() const;
        Rational operator+(const Rational& rhs) const;
        Rational operator-(const Rational& rhs) const { return (*this + -rhs); }
        Rational operator*(const Rational& rhs) const;
        Rational operator/(const Rational& rhs) const { return (*this * Rational(rhs.m_Denom, rhs.m_Numr)); }
        bool operator<(const Rational& rhs) const;
        bool operator>(const Rational& rhs) const  { return  (rhs < *this); }
        bool operator<=(const Rational& rhs) const { return !(rhs < *this); }
        bool operator>=(const Rational& rhs) const { return !(*this < rhs); }
        bool operator==(const Rational& rhs) const;
        bool operator!=(const Rational& rhs) const { return !(*this == rhs); }

    private:
        int m_Numr;
        int m_Denom;
};

#endif // RATIONAL_H
