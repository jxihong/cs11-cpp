#ifndef _STATE_HH_
#define _STATE_HH_

#include <memory>

template <typename T>
class State {

private:
  unsigned  _id;
  T _dist;

public:
  State( unsigned n, T dist ) : _id(n), _dist(dist) {}

  inline unsigned id() const { return _id; }

  inline T dist() const { return _dist; }

};
typedef State<float> StateF;
typedef State<double> StateD;
typedef State<int> StateI;


typedef std::shared_ptr<StateD> dStatePtr;

#endif // _STATE_HH_
