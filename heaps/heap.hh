#include <cassert>
#include <stdexcept>

template<typename T, int MAX_HEAP_ELEMS> class Heap {

private:
  int num_values;
  T values[MAX_HEAP_ELEMS];
  
  void swap_values(int i, int j);

  int LEFT_CHILD(int index) { return 2 * index + 1; }
  int RIGHT_CHILD(int index) { return 2 * index + 2; }
  int PARENT(int index) { return (index - 1) / 2; }

  void sift_down(int index);
  void sift_up(int index);

public:
  Heap() : num_values(0) {}
  ~Heap() {}

  T pop() {
    T result;
    
    if (num_values == 0) {
      throw std::underflow_error("Heap Empty");
    }

    result = values[0];

    num_values--;
    
    if (num_values != 0) {
      values[0] = values[num_values];
      sift_down(0);
    }
    
    return result;
  }

  void push (T newval) {
    int index;

    if (num_values >= MAX_HEAP_ELEMS) {
      throw std::overflow_error("Heap Full");
    }

    index = num_values;
    values[index] = newval;
    num_values++;

    if (index !=0) {
      sift_up(index);
    }
  }

};

template<typename T, int MAX_HEAP_ELEMS> 
void Heap<T, MAX_HEAP_ELEMS>::sift_down(int index) {
  assert (index < num_values);

  int left_child = LEFT_CHILD(index);
  int right_child = RIGHT_CHILD(index);

  if (left_child >= num_values){
    return;
  }
  else if (right_child >= num_values) {
    if (values[left_child] < values[index]) {
      swap_values(index, left_child);
    }
  }
  else {
    T left_val = values[left_child];
    T right_val = values[right_child];
    int swap_child;

    if (left_val < values[index] || right_val < values[index]) {
      if (left_val < right_val) {
	swap_child = left_child;
      }
      else {
	swap_child = right_child;
      }
      swap_values(index, swap_child);
      sift_down(swap_child);
    }
  }
}

template<typename T, int MAX_HEAP_ELEMS> 
void Heap<T, MAX_HEAP_ELEMS>::sift_up(int index) {
  int parent_index = PARENT(index);

  if (index == 0) {
    return;
  }

  assert (parent_index >= 0);
  assert (parent_index != index);

  
  if (values[index] < values[parent_index]) {
    swap_values(index, parent_index);
    
    if (parent_index != 0) {
      sift_up(parent_index);
    }
  }
}

template<typename T, int MAX_HEAP_ELEMS> inline
void Heap<T, MAX_HEAP_ELEMS>::swap_values(int i, int j) {
  T tmp;
  
  assert (i >= 0 && i < num_values);
  assert (j >= 0 && j < num_values);
  assert (i != j);

  tmp = values[i];
  values[i]=values[j];
  values[j] = tmp;
}
