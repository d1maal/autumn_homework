#include "graph.h"

#include <algorithm>
#include <vector>

Edge::Edge(int u, int v, int w) : u(u), v(v), w(w) {}

bool CompareEdges(const Edge& a, const Edge& b) { return a.w < b.w; }

DisjointSetUnion::DisjointSetUnion(int n) {
  parent.resize(n);
  rank.resize(n, 0);
  for (int i = 0; i < n; ++i) {
    parent[i] = i;
  }
}

int DisjointSetUnion::Find(int x) {
  if (parent[x] != x) {
    parent[x] = Find(parent[x]);
  }
  return parent[x];
}

void DisjointSetUnion::Unite(int x, int y) {
  x = Find(x);
  y = Find(y);
  if (x == y) return;
  if (rank[x] < rank[y]) {
    parent[x] = y;
  } else if (rank[x] > rank[y]) {
    parent[y] = x;
  } else {
    parent[y] = x;
    rank[x]++;
  }
}

long long FindMinimumSpanningTreeWithDegreeLimit(int n, int d,
                                                 std::vector<Edge>& edges) {
  std::sort(edges.begin(), edges.end(), CompareEdges);
  DisjointSetUnion dsu(n + 1);
  std::vector<int> degree(n + 1, 0);
  int edges_used = 0;
  long long total_weight = 0;

  for (const Edge& e : edges) {
    if (edges_used == n - 1) break;
    int u = e.u;
    int v = e.v;
    int w = e.w;
    if (dsu.Find(u) != dsu.Find(v) && degree[u] < d && degree[v] < d) {
      dsu.Unite(u, v);
      degree[u]++;
      degree[v]++;
      total_weight += w;
      edges_used++;
    }
  }

  if (edges_used == n - 1) {
    return total_weight;
  }
  return -1;
}