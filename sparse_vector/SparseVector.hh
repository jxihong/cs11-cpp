class SparseVector {

private:  
  int size;
  
  struct node
  {
    int   index;   // Element number, in the range [0, size)
    int   value;   // The value of this element.
    node *next;    // A pointer to the next node in the linked-list.

    // Node constructor - simply initializes the data-members.
    node(int index, int value, node *next = 0) : 
      index(index), value(value), next(next) { }
  };

  node *start;     // A pointer to the first node in the vector

  void clear();
  void copyList(const SparseVector &sv);
  void setNonzeroElem(int index, int value);
  void removeElem(int index);
  
  void addSubVector(const SparseVector &sv, bool add);
  void removeZeros();
  
  //Debug functions
  bool checkListOrder() const;
  bool checkZeros() const;
  void printListOrder() const;
  
public:
  SparseVector() : size(0), start(0) { }
  SparseVector(int size) : size(size), start(0) { }
  SparseVector(const SparseVector &sv);
  ~SparseVector();
  
  SparseVector & operator=(const SparseVector &sv);
  SparseVector & operator+=(const SparseVector &sv);
  SparseVector & operator-=(const SparseVector &sv);

  const SparseVector operator+(const SparseVector &sv) const;
  const SparseVector operator-(const SparseVector &sv) const;
  
  bool operator==(const SparseVector &sv) const;
  bool operator!=(const SparseVector &sv) const;
 
  int getSize() const { return size; }
  int getElem(int idx) const;
  void setElem(int index, int value);

};
  
