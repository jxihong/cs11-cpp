#include "../include/rational.h"

#include <stdexcept>
#include <ostream>
#include <iostream>

const Rational Rational::inverse() const {
  /* Return the Rational number 1 / current rational */
  if (_num == 0) {
    throw bad_rational();
  }
  return Rational(_denom, _num);
}

Rational::sign_type Rational::sign() const {
  /* Return, as a sign_type, the sign of the Rational */
  return to_double() < 0 ? Rational::NEGATIVE : Rational::POSITIVE;
}

/* Print the value num/den to the supplied output stream, or 0 if 
 * the Rational happens to be identically zero.
 */
std::ostream& operator<<( std::ostream &os, const Rational &ratio ) {
  if( ratio == 0 ) {
    os << "0";
  } else {
    if( ratio.sign() == Rational::NEGATIVE ) {
      os << "-";
    }
    os << std::abs( ratio.num() ) << "/" << std::abs( ratio.denom() );
  }
  return os;
}

/* This function will be called whenever the 
 * Rational is constructed from integers that
 * are supplied as numerator and denominator.
 * Rationals will be reduced to lowest terms, with 
 * negative signs only in the numerator 
 */
void Rational::normalize() {
  if (_denom == 0) {
    throw bad_rational();
  }
  intmax_t rat_gcd = gcd(std::abs(_num), std::abs(_denom));
  
  (sign() == Rational::negative) ? 
    _num = -1 * std::abs(_num) / rat_gcd : std::abs(_num) /= rat_gcd;
  _denom = std::abs(denom) / rat_gcd;  
}

// Return the float precision number corresponding to the Rational
float Rational::to_float() const {
  return (float)_num / (float) _denom;
}

// Return the double precision number corresponding to the Rational
double Rational::to_double() const {
  return (double) _num / (double) _denom;
}
