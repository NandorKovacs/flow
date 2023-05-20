#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int a, b, maxflow, currentflow = 0;

  int get_pair(int x) {
    if (x == a) return b;
    if (x == b) return a;
    assert(false);
  }

  bool outgoing(int x) { return x == a; }
};

int main() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;

  vector<Edge> e(m);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    cin >> e[i].a >> e[i].b >> e[i].maxflow;

    g[e[i].a].push_back(i);
    g[e[i].b].push_back(i);
  }

  vector<int> flow(n, 0);
  vector<int> height(n, 0);
  height[s] = n;

  priority_queue<pair<int, int>> active;
  for (int x : g[s]) {
    if (!e[x].outgoing(s)) {
      continue;
    }
    if (e[x].get_pair(s) != t) {
      active.push({0, e[x].get_pair(s)});
    }
    flow[e[x].get_pair(s)] += e[x].currentflow = e[x].maxflow;
  }

  while (active.size()) {
    int x = active.top().second;
    active.pop();
    if (active.size() == 0 && x == t) {
      break;
    }

    int doublebreak = false;
    for (int i : g[x]) {
      Edge &edge = e[i];
      int xpair = edge.get_pair(x);

      if (height[xpair] >= height[x]) {
        continue;
      }

      if (edge.outgoing(x)) {
        if (edge.currentflow >= edge.maxflow) {
          continue;
        }

        if (flow[xpair] == 0 && xpair != s && xpair != t) {
          active.push({height[xpair], xpair});
        }

        int residual = edge.maxflow - edge.currentflow;
        if (flow[x] <= residual) {
          edge.currentflow += flow[x];
          flow[xpair] += flow[x];
          flow[x] = 0;
          doublebreak = true;
          break;
        }
        flow[x] -= residual;
        edge.currentflow = edge.maxflow;
        flow[xpair] += residual;
      } else {
        if (edge.currentflow == 0) {
          continue;
        }

        if (flow[xpair] == 0 && xpair != s && xpair != t) {
          active.push({height[xpair], xpair});
        }

        if (flow[x] <= edge.currentflow) {
          flow[xpair] += flow[x];
          edge.currentflow -= flow[x];
          flow[x] = 0;
          doublebreak = true;
          break;
        }
        flow[xpair] += edge.currentflow;
        flow[x] -= edge.currentflow;
        edge.currentflow = 0;
      }
    }
    if (doublebreak) {
      continue;
    }
    ++height[x];
    active.push({height[x], x});
  }

  cout << flow[t] << endl;
}