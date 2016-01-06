#ifndef _LIST_H_
#define _LIST_H_

#include <cstddef>
#include <stdexcept>

#include "list_node.h"

template<typename T>
class ApplyFunction;

template<typename T>
class ReduceFunction;

template <typename T>
class ListNode;

template <typename T> class List {
 private:
  size_t _length;
  ListNode<T> *_begin;
  ListNode<T> *_back;

public: 
  // Can use outside as List::iterator type
  class iterator {
    friend class List<T>;
    ListNode<T> *_node;
  public:
    iterator( ListNode<T> *node );
    iterator& operator++();
    int& operator*();
    bool operator==( const iterator &rhs );
    bool operator!=( const iterator &rhs );
  };

  // Can use outside as List::const_iterator type
  class const_iterator {
    friend class List<T>;
    ListNode<T> *_node;
  public:
    const_iterator( ListNode<T> *node );
    const_iterator& operator++();
    const int& operator*();
    bool operator==( const const_iterator &rhs );
    bool operator!=( const const_iterator &rhs );
  };

  List();
  List( const List<T> &list );
  List<T>& operator=( const List<T> &list );
  List( List<T> &&list);
  List<T>& operator=( List<T> &&list );
  ~List();

  size_t length() const;
  int& value( size_t pos );
  int value( size_t pos ) const;
  bool empty() const;

  iterator begin();
  const_iterator begin() const;
  iterator back();
  const_iterator back() const;
  iterator end();
  const_iterator end() const;

  iterator find( int val);
  void append( int val );
  void deleteAll( int val );
  void insert( iterator pos, int val );
  
  void apply ( const ApplyFunction<T> &interface );
  
  T reduce ( const ReduceFunction<T> &interface ) const;

  void print() const;
  void clear();

private:
  ListNode<T>* node( iterator it ) { return it._node; }
  ListNode<T>* node( const_iterator it ) { return it._node; }
};

template<typename T>
List<T> merge(List<T> &list1, List<T> &list2);

class ListOutOfBounds : public std::range_error {
public:
  explicit ListOutOfBounds() : std::range_error( "List index out of bounds" ) {}
};

#endif // _CPPLIST_H_
