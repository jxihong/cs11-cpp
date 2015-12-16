#ifndef _RATIONAL_H
#define _RATIONAL_H

#include <cstdint>
#include <iosfwd>
#include <stdexcept>

#include "gcd.h"

class Rational {
  intmax_t _num, _denom;
 public:
  enum sign_type { POSITIVE, NEGATIVE }; // sign of rational
  
  Rational() : _num(0), _denom(1) {}
  Rational( intmax_t num ) : _num(num), _denom(1) {}
  Rational( intmax_t num, intmax_t denom ) : _num(num), _denom(denom) { normalize(); }
  
  // Copy Constructor
  Rational( const Rational &r ) : _num(r._num), _denom(r._denom) {}
  // Destructor
  ~Rational() {}
  
  // Assignment Operator
  inline Rational & operator=(const Rational &r) {
    if (this != &r) {
      _num = r._num;
      _denom = r._denom;
    }
    return *this;
  }
  
  inline intmax_t num() const { return _num; }
  inline intmax_t denom() const { return _denom; }
  
  void normalize();
  float to_float() const;
  double to_double() const;
  sign_type sign() const;
  const Rational inverse() const;
};

std::ostream& operator<<( std::ostream &os, const Rational &ratio );

// Comparison Operators
inline bool operator==( const Rational &lhs, const Rational &rhs ) {
  return (lhs.num() == rhs.num() && lhs.denom() == rhs.denom());
}

inline bool operator!=( const Rational &lhs, const Rational &rhs ) {
  return (lhs.num() != rhs.num() || lhs.denom() != rhs.denom());
}

inline bool operator<( const Rational &lhs, const Rational &rhs ) {
  return (lhs.to_double() < rhs.to_double());
}

inline bool operator>( const Rational &lhs, const Rational &rhs ) {
  return (lhs.to_double() > rhs.to_double());
}

inline bool operator<=( const Rational &lhs, const Rational &rhs ) {
  return (lhs.to_double() <= rhs.to_double());
}

inline bool operator>=( const Rational &lhs, const Rational &rhs ) {
  return (lhs.to_double() >= rhs.to_double());
}

inline Rational operator*( const Rational &a, const Rational &b ) {
  return Rational(a.num() * b.num(), a.denom() * b.denom());
}

inline Rational operator*( intmax_t f, const Rational &r) {
  return Rational(r.num() * f, r.denom() * f);
}

inline Rational operator*( const Rational &r, intmax_t f) {
  return Rational(r.num() * f, r.denom() * f);
}

// Unary Operator
inline Rational operator-( const Rational &r) {
  return Rational(-1 * r.num(), r.denom());
}

inline Rational operator+( const Rational &a, const Rational &b ) {
  intmax_t denom_lcm = lcm(a.denom(), b.denom());
  
  intmax_t new_num = a.num() * denom_lcm / a.denom() + b.num() * denom_lcm / b.denom();
  return Rational(new_num, denom_lcm);
}

inline Rational operator-( const Rational &a, const Rational &b ) {
  return a + (-b);
}

inline Rational operator/( const Rational &a, const Rational &b ) {
  return a * b.inverse();
}

// Exception class for undefined rationals
class bad_rational : public std::domain_error {
 public:
  explicit bad_rational() : std::domain_error( "Bad rational: zero denominator" ) {}
};

#endif // _RATIONAL_H
