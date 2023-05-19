#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int s, t, c, f;
  int rev;
};

bool operator==(Edge const& a, Edge const& b) {
  return a.s == b.s && a.t == b.t && a.c == b.c && a.f == b.f;
}

bool operator!=(Edge const& a, Edge const& b) {
  return !(a == b);
}

int main() {
  int n, m, s, t;
  std::cin >> n >> m >> s >> t;

  std::vector<std::vector<int>> g(n);
  std::vector<Edge> edges;

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;

    Edge e = {a, b, c, 0, nullptr}, e2 = {b, a, c, c, nullptr};
    edges.push_back(e);
    g[a].push_back(e);
    g[b].push_back(e2);
    g[a].back().rev = &g[b].back();
    g[b].back().rev = &g[a].back();
  }

  int flow = 0;
  while (true) {
    std::queue<int> q;
    q.push(s);
    std::vector<Edge*> visited(n, nullptr);

    while (q.size()) {
      int cur = q.front();
      q.pop();

      for (int i = 0; i < g[cur].size(); ++i) {
        Edge& e = g[cur][i];
        if (visited[e.t] == nullptr && e.t != s && e.c > e.f) {
          visited[e.t] = &g[cur][i];
          q.push(e.t);
        }
      }
    }
  
    if (visited[t] != nullptr) {
      int d = -1;
      for (Edge* e = visited[t]; e != nullptr; e = visited[e->s]) {
        if (d == -1) {
          d = e->c - e->f;
          continue;
        }
        d = std::min(d, e->c - e->f);
      }
     
      for (Edge* e = visited[t]; e->s != -1; e = visited[e->s]) {
        e->f += d;
        e->rev->f -= d;
      }
      flow += d;
    } else {
      break;
    }
  }

  std::cout << flow << std::endl;
}