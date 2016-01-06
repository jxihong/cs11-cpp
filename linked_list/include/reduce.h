#ifndef _REDUCE_H_
#define _REDUCE_H_
#include "list.h"

template <typename T> class ReduceFunction {
protected:
  virtual T function( T x, T y ) const = 0;
public:
  T reduce( const List<T> &list ) const;
  virtual T identity() const = 0;
  virtual ~ReduceFunction() {}
};

// An example ReduceFunction
template <typename T> class SumReduce : public ReduceFunction<T> {
  T function( T x, T y ) const;
public:
  SumReduce() {}
  ~SumReduce() {}
  T identity() const { return (T)0; }
};

// Another ReduceFunction
template <typename T> class ProductReduce : public ReduceFunction<T> {
  T function( T x, T y ) const;
public:
  ProductReduce() {}
  ~ProductReduce() {}
  T identity() const { return (T)1; }
};

#endif // _REDUCE_H_
