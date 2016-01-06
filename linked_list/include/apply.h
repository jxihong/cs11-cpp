#ifndef _APPLY_H_
#define _APPLY_H_
#include "list.h"

template <typename T> class ApplyFunction {
protected:
  virtual int function( T x ) const = 0;
public:
  void apply( List<T> &list ) const;
  virtual ~ApplyFunction() {}
};

// An example ApplyFunction (see apply.cpp)
template <typename T> class SquareApply : public ApplyFunction<T> {
  int function( T x ) const;
};

#endif // _CPPLIST_APPLY_H_
