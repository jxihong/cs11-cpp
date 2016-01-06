#include "../include/list.h"
#include "../include/apply.h"
#include "../include/reduce.h"

#include <iostream>

template <typename T>
List<T>::List() : _length(0), _begin(nullptr), _back(nullptr) {}


template <typename T>
List<T>::List( const List<T> &list ) : _length(0), _begin(nullptr), _back(nullptr) {
  for( auto it = list.begin(); it != list.end(); ++it ) {
    append( *it );
  } 
}

template <typename T>
List<T>& List<T>::operator=( const List<T> &list ) {
  if( this != &list ) {
    clear();
    for( auto it = list.begin(); it != list.end(); ++it ) {
      append( *it );
    } 
  }
  return *this;
}

template <typename T>
List<T>::List( List<T> &&list): _length(0), _begin(nullptr), _back(nullptr) {
  for (auto it = list.begin(); it != list.end(); ++it) {
    append(*it);
  }
  list._length = 0;
  list._begin = nullptr;
  list._back = nullptr;
}

template <typename T>
List<T>& List<T>::operator=( List<T> &&list ) {
  if (this != &list) {
    clear();
    for (auto it = list.begin(); it != list.end(); ++it) {
      append(*it);
    }
    list._length = 0;
    list._begin = nullptr;
    list._back = nullptr;
  }
  return *this;
}

template <typename T>
List<T>::~List() { clear(); }

template <typename T>
size_t List<T>::length() const { return _length; }

template <typename T>
int& List<T>::value( size_t pos ) {
  auto it = begin();
  for( size_t i = 0; i < pos && it != end(); ++it, ++i );
  if( it == end() ) {
    throw ListOutOfBounds();
  }

  return *it;
}

template <typename T>
int List<T>::value( size_t pos ) const {
  auto it = begin();
  for( size_t i = 0; i < pos && it != end(); ++it, ++i );
  if( it == end() ) {
    throw ListOutOfBounds();
  }

  return *it;
}

template <typename T>
bool List<T>::empty() const {
  return _length == 0;
}

template <typename T>
typename List<T>::iterator List<T>::begin() { return iterator{ _begin }; }

template <typename T>
typename List<T>::const_iterator List<T>::begin() const { return const_iterator{ _begin }; }

template <typename T>
typename List<T>::iterator List<T>::back() { return iterator{ _back }; }

template <typename T>
typename List<T>::const_iterator List<T>::back() const { return const_iterator{ _back }; }

template <typename T>
typename List<T>::iterator List<T>::end() { return iterator{ nullptr }; }

template <typename T>
typename List<T>::const_iterator List<T>::end() const { return const_iterator{ nullptr }; }

template <typename T>
void List<T>::append( int val ) {
  auto *newNode = ListNode<T>::create( val );

  if( empty() ) {
    newNode->setNext( _back );
    _begin = newNode;
  } else {
    newNode->insertAfter( _back );
  }

  _back = newNode;
  ++_length;
}

template <typename T>
void List<T>::deleteAll( int val ) {
  if( !empty() ) {
    // Delete from the front
    while( _begin->value() == val && _begin != _back ) {
      auto *newBegin = _begin->next();
      delete _begin;
      _begin = newBegin;
      --_length;
    }

    auto *p = _begin;

    if( _begin != _back ) {
      // Normal deletion from interior of list
      for( ; p->next() != _back; ) {
        if( p->next()->value() == val ) {
          ListNode<T>::deleteNext( p );
          --_length;
        } else {
          p = p->next();
        }
      }

      // Deleting the last item
      if( _back->value() == val ) {
        ListNode<T>::deleteNext( p );
        _back = p;
        --_length;
      }
    } else if( _begin->value() == val ) {
      // Deal with the case where we deleted the whole list
      _begin = _back = nullptr;
      _length = 0;
    }
  }
}

// Inserts new node behind the node pointed to be iterator
template <typename T>
void List<T>::insert ( iterator pos, int val) {
  auto *node = pos._node;
  auto *next = node->next();

  auto *newNode = ListNode<T>::create(val);
  newNode->insertAfter(node);
  newNode->setNext(next);
}

// Finds first instance and returns iterator to it
template <typename T>
typename List<T>::iterator List<T>::find(int val) {
  for( auto it = begin(); it != end(); ++it ) {
    if( *it == val ) {
      return it;
    }
  }
  return end();
}

template <typename T>
void List<T>::apply( const ApplyFunction<T> &interface) {
  return interface.apply(*this);
}

template <typename T>
T List<T>::reduce( const ReduceFunction<T> &interface) const{
  return interface.reduce(*this);
}

template <typename T>
void List<T>::print() const {
  std::cout << "{ ";
  for( auto it = begin(); it != back(); ++it ) {
    std::cout << *it << " -> ";
  }
  if( !empty() ) {
    std::cout << *back() << " ";
  }
  std::cout << "}\n";
}

template <typename T>
void List<T>::clear() {
  for( auto *p = _begin; p != nullptr; ) {
    auto *p_next = p->next();
    delete p;
    p = p_next;
  }
  _length = 0;
  _begin = nullptr;
  _back = nullptr;
}

template <typename T>
List<T> merge(List<T> &list1, List<T> &list2) {
  List<T> mergeList(list1);
  for (auto it = list2.begin(); it != list2.end(); ++it) {
    mergeList.append(*it);
  }
  return mergeList;
}
