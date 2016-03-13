#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "heap.hh"

using namespace std;

void test_int_order() {
  Heap<int, 1000> hInt;

  srand((unsigned)time(0));
  for (int i = 0; i < 1000; i++) {
    hInt.push(rand() % 1000);
  }

  int lastval = hInt.pop();
  cout << "Value 0 = " << lastval << endl;

  for (int i = 1; i < 1000; i++) {
    int val = hInt.pop();
    
    cout << "Value " << i << " = " << val << endl;
    if (val < lastval) {
      cout << "OUT OF ORDER" << endl;
      return;
    }
    
    lastval = val;
  }
}

void test_string_order() {
  Heap<string, 10> hString;

  string fruits[] ={"apple", "banana" , "peach", "pear" , "grapes" , "watermelon", "strawberries" , "grapefruit", "cantalope", "pomegranate"};

  for (int i = 0; i < 10; i++) {
    hString.push(fruits[i]);
  }

  string laststr = hString.pop();
  cout << "Value 0 = " << laststr << endl;

  for (int i = 1; i < 10; i++) {
    string str = hString.pop();
    
    cout << "Value " << i << " = " << str << endl;
    if (str < laststr) {
      cout << "OUT OF ORDER" << endl;
      return;
    }
    
    laststr = str;
  }
}

void test_underflow() {
  try {
    Heap<int, 4> hInt;
    hInt.pop();
  }
  catch (underflow_error &e) {
    cout << "Underflow Error Success!" << endl;
  }
  catch (...) {
    cout << "Wrong Error Thrown" << endl;
  }
}

void test_overflow() {
  try {
    Heap<int, 4> hInt;
    for (int i = 0; i <= 4; i++) {
      hInt.push(i);
    } 
    cout << "No Error Thrown" << endl;
  }
  catch (overflow_error &e) {
    cout << "Overflow Error Success!" << endl;
  }
  catch (...) {
    cout << "Wrong Error Thrown" << endl;
  }
}

int main()
{
  test_int_order();
  cout << endl;

  test_string_order();
  cout << endl;

  test_underflow();
  test_overflow();

  return 0;
}
