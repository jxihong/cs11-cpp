#include "../include/list.h"

template <typename T>
List<T>::iterator::iterator( ListNode<T> *node ) : _node(node) {}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++() { 
  _node = _node->next(); 
  return *this; 
}

template <typename T>
int& List<T>::iterator::operator*() { return _node->value(); }

template <typename T>
bool List<T>::iterator::operator==( const iterator &rhs ) { return _node == rhs._node; }

template <typename T>
bool List<T>::iterator::operator!=( const iterator &rhs ) { return _node != rhs._node; }

template <typename T>
List<T>::const_iterator::const_iterator( ListNode<T> *node ) : _node(node) {}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() { 
  _node = _node->next(); 
  return *this; 
}

template <typename T>
const int& List<T>::const_iterator::operator*() { return _node->value(); }

template <typename T>
bool List<T>::const_iterator::operator==( const const_iterator &rhs ) { return _node == rhs._node; }

template <typename T>
bool List<T>::const_iterator::operator!=( const const_iterator &rhs ) { return _node != rhs._node; }
