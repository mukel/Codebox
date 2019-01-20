/*
 * Bron-Kerbosch algorithm to enumerate all maximal cliques.
 * Variations:
 *   Maximum clique.
 *   Maximum independent set.
 * Complexity: O(3^(n/3))
 * Verified:
 *   https://codeforces.com/contest/1105/problem/E
 */
#include <bits/stdc++.h>
using namespace std;

namespace bron_kerbosch {
  typedef long long bits;
  typedef vector<bits> graph;
  /**
   * Given three disjoint sets of vertices R, P, and X, finds the maximal cliques that include:
   *   - all of the vertices in R
   *   - some of the vertices in P
   *   - none of the vertices in X
   */
  void rec(bits R, bits P, bits X, const graph& G, const function<void(bits)>& callback) {
    if (P == 0 && X == 0) {
      callback(R);
      return ;
    }
    int u = 0; while (!((P | X) & (1LL << u))) ++u;
    for (int v = 0; v < (int) G.size(); ++v) {
        if ((P & ~G[u]) & (1LL << v)) {
          rec(R | (1LL << v), P & G[v], X & G[v], G, callback);
          P &= ~(1LL << v);
          X |= (1LL << v);
        }
    }
  }
  void enumerate_maximal_cliques(const graph& G, const function<void(bits)>& callback) {
    rec(0, (1LL << G.size()) - 1, 0, G, callback);
  }
  int max_clique(const graph& G) {
    int ans = 0;
    enumerate_maximal_cliques(G, [&ans](bits R) { ans = max(ans, (int) __builtin_popcountll(R)); });
    return ans;
  }
};

const int MAXV = 40;

int Q, V;
map<string, int> name2id;

int main() {
  ios_base::sync_with_stdio(0);

  cin >> Q >> V;
  bron_kerbosch::graph G(V);
  for (int i = 0; i < Q; ++i) {
    bron_kerbosch::bits seen = 0;
    while (i < Q) {
      int op; cin >> op;
      if (op == 1) break;
      string s; cin >> s;
      if (!name2id.count(s)) {
        int newId = name2id.size();
        name2id[s] = newId;
      }
      seen |= (1LL << name2id[s]);
      ++i;
    }
    for (int k = 0; k < V; ++k)
      if (seen & (1LL << k))
        G[k] |= seen;
  }

  // G^-1
  for (int i = 0; i < V; ++i)
    G[i] = ~G[i] & ((1LL << V) - 1);

  // max_independent_set(G) = max_clique(G^1)
  cout << bron_kerbosch::max_clique(G);
  return 0;
}
