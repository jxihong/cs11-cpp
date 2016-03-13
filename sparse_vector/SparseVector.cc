#include "SparseVector.hh"

#include <cassert>
#include <iostream>

using namespace std;

void SparseVector::clear() {
  node *curr = start;
  
  while (curr != 0) {
    node *next = curr->next;
    delete curr;
    curr = next;
  }
  start = 0;
}

void SparseVector::copyList(const SparseVector &sv) {
  size = sv.size;
  start = 0;

  node *otherCurr = sv.start;
  node *prev = 0;
 
  while (otherCurr != 0) {
    node *curr = new node(otherCurr->index, otherCurr->value);
    
    if (prev == 0) {
	start = curr;
    }
    else {
      prev->next = curr;
    }
    prev = curr;
    otherCurr = otherCurr->next;
  }
  assert (checkListOrder());
  assert (checkZeros());
}

void SparseVector::setNonzeroElem(int index, int value) {
  assert (value != 0);  
  
  node *prev = 0;
  node *curr = start;
  
  if (curr == 0) {
    start = new node(index, value);
  }
  
  while (curr != 0) {
    if (curr->index == index) {
      curr->value = value;
      break;
    }
    if (curr->index > index) {
      if (prev == 0) {
      	start = new node(index, value, curr);
      }
      else {
	prev->next  = new node(index, value, curr);
      }
      break;
    }
    if (curr->next == 0) {
      curr->next  = new node(index, value);
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  assert (checkListOrder());
}

void SparseVector::removeElem(int index) {
  node *prev = 0;
  node *curr = start;
  
  while (curr !=0) {
    if (curr->index == index) {
      if (prev == 0) {
	start=curr->next;
      }
      else {
	prev->next=curr->next;
      }
      delete curr;
      break;
    }
    if (curr->index > index) {
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  assert (checkListOrder());
}

void SparseVector::addSubVector(const SparseVector &sv, bool add) {
  node *curr = start;
  node *prev = 0;
  node *otherCurr = sv.start;
  
  int sign = (add ? 1 : -1);
  while (curr != 0 && otherCurr != 0) {
    if (curr->index < otherCurr->index) {
      prev = curr;
      curr = curr->next;
    }
    else if (curr->index == otherCurr->index) {
      curr->value = curr->value + sign * otherCurr->value;
      prev = curr;
      curr = curr->next;
      otherCurr = otherCurr->next;
    }
    else { //Node index is greater than other node's index
      if (prev == 0) {
	prev = new node(otherCurr->index, sign * otherCurr->value, curr);
	start = prev;
      }
      else {
	prev->next = new node(otherCurr->index, sign * otherCurr->value, curr);
	prev = prev->next;
      }
      otherCurr = otherCurr->next;
    }
  }
  while (otherCurr != 0) {
    curr = new node(otherCurr->index, sign * otherCurr->value);
    if (prev == 0) {
      start = curr;
    }
    else {
      prev->next = curr;
    }
    prev = curr;
    curr = curr->next;
    otherCurr = otherCurr->next; 
  }
  removeZeros();
  assert (checkZeros());
}

void SparseVector::removeZeros() {
  node *curr = start;
  node *prev = 0;
  while (curr != 0) {
    node *next = curr->next;
    if (curr->value == 0) {
      if (prev == 0) {
	start = next;
      }
      else {
	prev->next = next;
      }
      delete curr;
      curr = next;
    }
    else {
      prev = curr;
      curr = next;
    }
  }      
}

SparseVector::SparseVector(const SparseVector &sv) {
  copyList(sv);
}

SparseVector::~SparseVector() {
  clear();
}

SparseVector& SparseVector::operator=(const SparseVector &sv) {
  if (this != &sv) {
    clear();
    copyList(sv);
  }
  return *this;
}

SparseVector& SparseVector::operator+=(const SparseVector &sv) {
  if (this != &sv) {
    addSubVector(sv, true);
  }
  return *this;
}

SparseVector& SparseVector::operator-=(const SparseVector &sv) {
  if (this != &sv) {
    addSubVector(sv, false);
  }
  return *this;
}

const SparseVector SparseVector::operator+(const SparseVector &sv) const {
  return SparseVector(*this) += sv;
}

const SparseVector SparseVector::operator-(const SparseVector &sv) const {
  return SparseVector(*this) -= sv;
}

bool SparseVector::operator==(const SparseVector &sv) const {
  node *curr = start;
  node *otherCurr = sv.start;

  if (size != sv.size) {
    return false;
  }

  while (curr != 0 && otherCurr !=0) {
    if (curr->index != otherCurr->index) {
      return false;
    }
    else if (curr->value != otherCurr->value) {
      return false;
    }
    else {
      curr = curr->next;
      otherCurr = otherCurr->next;
    }
  }
  if (curr != 0 || otherCurr != 0) {
    return false;
  }
  return true;
}

bool SparseVector::operator!=(const SparseVector &sv) const {
  return !(*this == sv);
}

int SparseVector::getElem(int idx) const {
  assert (checkListOrder());
  
  node *curr = start;

  while (curr != 0) {
    if (curr->index > idx) {
      return 0;
    }
    if (curr->index == idx) {
      return curr->value;
    }
    curr = curr->next;
  }
  return 0;
}

void SparseVector::setElem(int index, int value) {
  if (value == 0) {
    removeElem(index);
  }
  else {
    setNonzeroElem(index, value);
  }
}

bool SparseVector::checkListOrder() const {
  node *curr = start;
  node *prev = 0;

  bool pass = true;
  while (curr != 0) {
    if (prev != 0) {
      if (prev->index > curr->index) {
	cout<<"Out of Order: " << prev->index << ":" << prev->value << " & "
	    << curr->index << ":" << curr->value << endl;
	pass = false;
      }
    }
    prev=curr;
    curr = curr->next;
  }
  return pass;
}

bool SparseVector::checkZeros() const {
  node *curr = start;
  
  while (curr != 0) {
    if (curr->value == 0) {
      cout<< "Remove: " << curr->index << ":" <<curr->value << endl;
      return false;
    }
    curr = curr->next;
  }
  return true;
}

void SparseVector::printListOrder() const {
  node *curr = start;

  while (curr != 0) {
    cout << curr->index << ":" << curr->value << " ; ";
    curr=curr->next;
  }
  cout<<endl;
}
