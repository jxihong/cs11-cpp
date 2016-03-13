#include "AdjacencyList.hh"

inline bool operator<( const dStatePtr &a, const dStatePtr &b ) {
  return a->dist() > b->dist();
}

AdjacencyList::AdjacencyList( std::istream &input ) : _adj(){
  size_t nNodes;
  unsigned nEdges;
  input >> nNodes >> nEdges;

  _adj.resize(nNodes);

  for (unsigned i = 0; i < nEdges; i++) {
    unsigned v, w; // ids of the two states
    double distance;
    
    input >> v >> w >> distance;
    // Add undirected edge
    _adj[v].push_back( dStatePtr(new StateD(w, distance)) );
    _adj[w].push_back( dStatePtr(new StateD(v, distance)) );
  }
}
 
void AdjacencyList::print() {
  for (size_t i = 0; i < _adj.size(); i++) {
    std::cout << i << ": ";
    for (auto statePtr : _adj[i]) {
      std::cout << std::fixed << std::setprecision( 1 );
      std::cout << "(" << statePtr->id() << ", " << statePtr->dist() << ") ";
    }
    std::cout << std::endl;
  }
}

double MST_Prim( const AdjacencyList &adj) {
  std::unordered_map<unsigned, bool> visited;
  std::priority_queue<dStatePtr> minQ;

  minQ.push( dStatePtr(new StateD(0, 0.0)));
  double treeWeight = 0.0;

  while (visited.size() < adj.size()) {
    auto top = minQ.top();
    minQ.pop();

    if ( visited.count(top->id()) == 0 ) {
      visited[top->id()] = true;
      treeWeight += top->dist();

      for ( auto statePtr : adj.adj(top->id()) ) {
	minQ.push(statePtr);
      }
    }
  }
  return treeWeight;
}
  
int main() {
  std::ifstream input( "mst.in" );
  std::ofstream output( "mst.out" );

  if (input.is_open() ) {
    auto adj = AdjacencyList(input);
    adj.print();
    output << std::fixed << std::setprecision( 8 );
    output << MST_Prim(adj) << std::endl;
  }
  else {
    std::cerr << "Couldn't open file" << std::endl;
    return -1;
  }

  return 0;
}
