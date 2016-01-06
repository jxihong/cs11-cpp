#include "../include/list.h"
#include "../include/reduce.h"

template <typename T>
T ReduceFunction<T>::reduce( const List<T> &list ) const {
  T result = identity();
  for( auto it = list.begin(); it != list.end(); ++it ) {
    result = function( result, *it );
  }
  return result;
}

template <typename T>
T SumReduce<T>::function( T x, T y ) const { 
  return x + y; 
}

template <typename T>
T ProductReduce<T>::function( T x, T y ) const { 
  return x * y; 
}
