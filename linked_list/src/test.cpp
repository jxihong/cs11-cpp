#include "../include/list.h"
#include "../include/apply.h"
#include "../include/reduce.h"
#include <iostream>

int main() {
  try { 
    int N = 100;
    List testList;

    for( int i = 0; i < N; ++i ) {
      testList.append( i );
    }

    List testList2;
    testList2 = testList;
    testList2.append( 5 );
    testList2.deleteAll( 0 );
    testList2.deleteAll( N );
    testList2.deleteAll( N - 1 );
    List testList3(testList2);

    std::cout << "value(0)=" << testList3.value( 0 ) << '\n';
    std::cout << "value(1)=" << testList3.value( 1 ) << '\n';
    std::cout << "value(" << testList3.length() - 1 << ")=" << testList3.value(testList3.length() - 1 ) << '\n';
    
    testList3 = merge(testList3, testList);
    testList3.apply( SquareApply() );
    std::cout << "apply^2 & reduce+: " << testList3.reduce( SumReduce() ) << "\n";
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << e.what() << "\n";
    return -1;
  }
}
