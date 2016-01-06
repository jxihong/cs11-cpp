#include "../include/list.h"
#include "../include/apply.h"

template<typename T>
void ApplyFunction<T>::apply( List<T> &list ) const {
  for( auto it = list.begin(); it != list.end(); ++it ) {
    *it = function( *it );
  }
}

template<typename T>
int SquareApply<T>::function( T x ) const {
  return x * x;
}
