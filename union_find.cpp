#include <bits/stdc++.h>
using namespace std;

/**
 * Union-Find data structure, link-by-size + path compression.
 * 
 * Theorem. [Tarjan 1975]
 * Link-by-size with path compression performs any intermixed sequence of 
 * m ≥ n FIND and n – 1 UNION operations in O(m * α(m, n)) time, where 
 * α(m, n) is a functional inverse of the Ackermann function.
 */
struct union_find {
  vector<int> data;
  
  union_find(int n) : data(n, -1) {}
  
  int find(int u) { return (data[u] < 0) ? u : data[u] = find(data[u]); }
  
  int find_non_rec(int u) {
    int p = u;
    while (data[p] >= 0) p = data[p];
    while (data[u] >= 0) {
      int tmp = data[u];
      data[u] = p;
      u = tmp;
    }
    return p;
  }
  
  int size(int u) { return -data[find(u)]; }

  bool join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return 0;
    if (size(u) < size(v)) swap(u, v);
    data[u] += data[v];
    data[v] = u;
    return 1;
  }
};

// Example usage, simple incremental connectivity problem.
int main() {
  int V, Q; cin >> V >> Q;
  
  union_find uf(V);
  while (Q--) {
    string op;
    int u, v;
    cin >> op >> u >> v;
    --u;
    --v;
    
    if (op == "QUERY") {
      if (uf.find(u) == uf.find(v))
        cout << "CONNECTED\n";
      else
        cout << "NOT CONNECTED\n";
    }
    else if (op == "UNION")
      uf.join(u, v);
  }
  
  return 0;
}
