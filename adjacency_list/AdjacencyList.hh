#ifndef _ADJLIST_HH_
#define _ADJLIST_HH_

#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "State.hh"

class AdjacencyList {

private:
  std::vector< std::vector<dStatePtr> >_adj;
  AdjacencyList() = delete;

public:
  AdjacencyList( std::istream &input );

  inline size_t size() const { return _adj.size(); }

  inline const std::vector<dStatePtr>& adj( unsigned id ) const {
    return _adj[id];
  }

  void print();
};

#endif // _ADJLIST_HH_
