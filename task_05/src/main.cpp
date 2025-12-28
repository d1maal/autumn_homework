#include <iostream>
#include <vector>
#include "graph.h"

int main() {
  int n, m, d;
  std::cin >> n >> m >> d;

  std::vector<Edge> edges;
  edges.reserve(m);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    if (u != v) {
      edges.push_back(Edge(u, v, w));
    }
  }

  long long result = FindMinimumSpanningTreeWithDegreeLimit(n, d, edges);

  if (result != -1) {
    std::cout << result << std::endl;
  } else {
    std::cout << "Невозможно построить остовное дерево с заданным ограничением "
                 "степени"
              << std::endl;
  }

  return 0;
}