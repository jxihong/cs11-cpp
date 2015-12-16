#ifndef _LIST_NODE_H
#define _LIST_NODE_H

/* 
 * Defines a node in a linked_list
 */
template <typename T> class ListNode {
 private:  
  T _value;
  ListNode<T> *_next;
  
  // Remove copy and assignment
  ListNode( const ListNode & ) = delete;
  ListNode& operator=( const ListNode & ) = delete;
public:
 ListNode(): _value((T) 0 ), _next(nullptr) {}
 ListNode( T val ): _value(val), _next(nullptr) {}
  ~ListNode() {}
  inline T & value() { return _value; }
  inline T value() const { return _value; }
  inline ListNode<T>* next() const { return _next; }
  
  inline void insertAfter( ListNode<T> *before ) {
    _next = before -> _next;
    before->_next = this;
  }
  inline void setNext( ListNode<T> *nextNode ) { _next = nextNode; }

  static void deleteNext( ListNode<T> *before ) {
    auto *new_next = before->next()->next();
    delete before->next();
    before->_next = new_next;
  }

  static void deleteSection( ListNode<T> *before, ListNode<T> *after ) {
    auto *front = before->next();
    while (front != after) {
      auto *next = front -> next();
      delete front;
      front = next;
    }
  }
  
  static ListNode<T>* create( T val) {
    return new ListNode(val);
  }

};

typedef ListNode<int> ListNodeI;
typedef ListNode<float> ListNodeF;
typedef ListNode<double> ListNodeD;

#endif // _LIST_NODE_H
