#include <iostream>
#include <queue>
#include <vector>

#define int long long

struct Edge {
  int s, t, c, f;
  int rev;
};

bool operator==(Edge const& a, Edge const& b) {
  return a.s == b.s && a.t == b.t && a.c == b.c && a.f == b.f;
}

bool operator!=(Edge const& a, Edge const& b) { return !(a == b); }



signed main() {
  int n, m, s, t;
  std::cin >> n >> m >> s >> t;

  std::vector<std::vector<int>> g(n);
  std::vector<Edge> edges;

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;

    Edge e = {a, b, c, 0, edges.size() + 1}, e2 = {b, a, c, c, edges.size()};
    g[a].push_back(edges.size());
    g[b].push_back(edges.size() + 1);
    edges.push_back(e);
    edges.push_back(e2);
  }

  int flow = 0;
  while (true) {
    std::queue<int> q;
    q.push(s);
    std::vector<int> visited(n, -1);

    while (q.size()) {
      int cur = q.front();
      q.pop();

      for (int i = 0; i < g[cur].size(); ++i) {
        Edge& e = edges[g[cur][i]];
        if (visited[e.t] == -1 && e.t != s && e.c > e.f) {
          visited[e.t] = g[cur][i];
          q.push(e.t);
        }
      }
    }

    if (visited[t] != -1) {
      int d = INT64_MAX;
      for (int i = visited[t]; i != -1; i = visited[edges[i].s]) {
        d = std::min(d, edges[i].c - edges[i].f);
      }

      for (int i = visited[t]; i != -1; i = visited[edges[i].s]) {
        edges[i].f += d;
        edges[edges[i].rev].f -= d;
      }
      flow += d;
    } else {
      break;
    }
  }

  std::cout << flow << std::endl;
}