#ifndef _LIST_H_
#define _LIST_H_

#include <cstddef>
#include <stdexcept>

#include "list_node.h"

class ApplyFunction;
class ReduceFunction;
template <typename T>
class ListNode;

class List {
 private:
  size_t _length;
  ListNodeI *_begin;
  ListNodeI *_back;

public: 
  // Can use outside as List::iterator type
  class iterator {
    friend class List;
    ListNodeI *_node;
  public:
    iterator( ListNodeI *node );
    iterator& operator++();
    int& operator*();
    bool operator==( const iterator &rhs );
    bool operator!=( const iterator &rhs );
  };

  // Can use outside as List::const_iterator type
  class const_iterator {
    friend class List;
    ListNodeI *_node;
  public:
    const_iterator( ListNodeI *node );
    const_iterator& operator++();
    const int& operator*();
    bool operator==( const const_iterator &rhs );
    bool operator!=( const const_iterator &rhs );
  };

  List();
  List( const List &list );
  List& operator=( const List &list );
  List( List &&list);
  List& operator=( List &&list );
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
  
  void apply( const ApplyFunction &interface );

  int reduce( const ReduceFunction &interface ) const;
  
  void print() const;
  void clear();

private:
  ListNodeI* node( iterator it ) { return it._node; }
  ListNodeI* node( const_iterator it ) { return it._node; }
};

List merge(List &list1, List &list2);

class ListOutOfBounds : public std::range_error {
public:
  explicit ListOutOfBounds() : std::range_error( "List index out of bounds" ) {}
};

#endif // _CPPLIST_H_
