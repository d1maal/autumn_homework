#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
  int u, v, w;
  Edge(int u, int v, int w);
};

bool CompareEdges(const Edge& a, const Edge& b);

class DisjointSetUnion {
 public:
  explicit DisjointSetUnion(int n);
  int Find(int x);
  void Unite(int x, int y);

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

long long FindMinimumSpanningTreeWithDegreeLimit(int n, int d,
                                                 std::vector<Edge>& edges);

#endif  // GRAPH_H