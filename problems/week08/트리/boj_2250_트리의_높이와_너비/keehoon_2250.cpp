// 2250 – 트리의 높이와 너비
// https://www.acmicpc.net/problem/2250
// solved.ac: https://solved.ac/search?query=2250
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold II
// 태그: 그래프 이론, 그래프 탐색, 깊이 우선 탐색, 트리
// 푼 사람 수: 5,082
// 평균 시도: 3.47

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 표준입력이 터미널이면 input.txt로 대체 (파이프 입력 시에는 그대로 cin)
#if defined(_WIN32)
  if (_isatty(_fileno(stdin)))
  {
    freopen("input.txt", "r", stdin);
  }
#else
  if (isatty(fileno(stdin)))
  {
    freopen("input.txt", "r", stdin);
  }
#endif

  struct Node
  {
    int node, left_node, right_node;

    Node() : node(0), left_node(0), right_node(0) {}
    Node(int node, int left_node, int right_node) : node(node), left_node(left_node), right_node(right_node) {}

    bool operator<(const Node &other) const
    {
      return node < other.node;
    }
  };

  int N;
  cin >> N;

  vector<Node> adjacency_list(N + 1);
  vector<int> in_degrees(N + 1);
  for (int i = 1; i <= N; ++i)
  {
    cin >> adjacency_list[i].node >> adjacency_list[i].left_node >> adjacency_list[i].right_node;

    if (adjacency_list[i].left_node != -1)
      ++in_degrees[adjacency_list[i].left_node];

    if (adjacency_list[i].right_node != -1)
      ++in_degrees[adjacency_list[i].right_node];
  }

  sort(adjacency_list.begin(), adjacency_list.end());

  int root;
  for (int i = 1; i <= N; ++i)
    if (in_degrees[i] == 0)
    {
      root = i;
      break;
    }

  vector<vector<int>> cols(N + 1);
  int col = 0;
  int max_level = 0;
  auto inorder = [&](auto &&self, int cur, int level) -> void
  {
    max_level = max(max_level, level);

    if (adjacency_list[cur].left_node != -1)
      self(self, adjacency_list[cur].left_node, level + 1);

    cols[level].push_back(++col);

    if (adjacency_list[cur].right_node != -1)
      self(self, adjacency_list[cur].right_node, level + 1);
  };

  inorder(inorder, root, 1);

  auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) -> bool
  {
    if (a.first != b.first)
      return a.first > b.first;
    return a.second < b.second;
  };

  set<pair<int, int>, decltype(cmp)> widths(cmp);
  for (int level = 1; level <= max_level; ++level)
    widths.emplace(*max_element(cols[level].begin(), cols[level].end()) - *min_element(cols[level].begin(), cols[level].end()) + 1, level);

  cout << widths.begin()->second << ' ' << widths.begin()->first;

  return 0;
}
