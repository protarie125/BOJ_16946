#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using vs = vector<string>;
using vb = vector<bool>;
using vvb = vector<vb>;
using Pos = pair<ll, ll>;

ll N, M;
vs Map;
vvb visit;
vl areas;
vvl labels;

vl dr{-1, 1, 0, 0};
vl dc{0, 0, -1, 1};

void Bfs(ll r, ll c, ll lab) {
  queue<Pos> Q{};
  Q.push({r, c});
  visit[r][c] = true;

  ll area = 0;
  while (!Q.empty()) {
    auto [fr, fc] = Q.front();
    Q.pop();

    ++area;
    labels[fr][fc] = lab;

    for (auto d = 0; d < 4; ++d) {
      const auto& nr = fr + dr[d];
      const auto& nc = fc + dc[d];

      if (nr < 0 || N <= nr || nc < 0 || M <= nc) continue;
      if (Map[nr][nc] == '1') continue;
      if (visit[nr][nc]) continue;

      Q.push({nr, nc});
      visit[nr][nc] = true;
    }
  }

  areas.push_back(area);
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> M;
  Map = vs(N);
  for (auto&& s : Map) cin >> s;

  areas = vl{};
  visit = vvb(N, vb(M, false));
  labels = vvl(N, vl(M, 0));
  auto lab = 0;
  for (auto i = 0; i < N; ++i) {
    for (auto j = 0; j < M; ++j) {
      if (Map[i][j] == '1') continue;
      if (visit[i][j]) continue;

      Bfs(i, j, lab);

      ++lab;
    }
  }

  for (auto i = 0; i < N; ++i) {
    for (auto j = 0; j < M; ++j) {
      if (Map[i][j] == '0') {
        cout << 0;
        continue;
      }

      auto usedlab = set<ll>{};
      auto x = 1;
      for (auto d = 0; d < 4; ++d) {
        const auto& nr = i + dr[d];
        const auto& nc = j + dc[d];

        if (nr < 0 || N <= nr || nc < 0 || M <= nc) continue;
        if (Map[nr][nc] == '1') continue;

        const auto& lab = labels[nr][nc];
        if (usedlab.find(lab) != usedlab.end()) continue;

        usedlab.insert(lab);
        x += areas[lab];
        x %= 10;
      }

      cout << x;
    }
    cout << '\n';
  }

  return 0;
}