// 21944 – 문제 추천 시스템 Version 2
// https://www.acmicpc.net/problem/21944
// solved.ac: https://solved.ac/search?query=21944
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold II
// 태그: 자료 구조, 집합과 맵, 트리를 사용한 집합과 맵
// 푼 사람 수: 748
// 평균 시도: 3.47

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

  const int MAX_PID = 1e5 + 1;

  int N;
  cin >> N;

  vector<vector<set<int>>> problems(101, vector<set<int>>(101));
  vector<pair<int, int>> metadatas(1e5 + 1);
  while (N--)
  {
    int P, L, G;
    cin >> P >> L >> G;
    problems[L][G].insert(P);
    metadatas[P] = make_pair(L, G);
  }

  int M;
  cin >> M;
  while (M--)
  {
    string command;
    cin >> command;

    if (command == "recommend")
    {
      int G, x;
      cin >> G >> x;

      if (x == 1)
      {
        for (int l = 100; l > 0; --l)
          if (problems[l][G].size())
          {
            cout << *problems[l][G].rbegin() << '\n';
            break;
          }
      }

      else if (x == -1)
      {
        for (int l = 1; l <= 100; ++l)
          if (problems[l][G].size())
          {
            cout << *problems[l][G].begin() << '\n';
            break;
          }
      }
    }

    else if (command == "recommend2")
    {
      int x;
      cin >> x;

      if (x == 1)
      {
        int result = 0;
        for (int l = 100; l > 0; --l)
        {
          for (int g = 1; g <= 100; ++g)
            if (problems[l][g].size() && result < *problems[l][g].rbegin())
              result = *problems[l][g].rbegin();

          if (result)
          {
            cout << result << '\n';
            break;
          }
        }
      }

      else if (x == -1)
      {
        int result = MAX_PID;
        for (int l = 1; l <= 100; ++l)
        {
          for (int g = 1; g <= 100; ++g)
            if (problems[l][g].size() && result > *problems[l][g].begin())
              result = *problems[l][g].begin();

          if (result < MAX_PID)
          {
            cout << result << '\n';
            break;
          }
        }
      }
    }

    else if (command == "recommend3")
    {
      int x, L;
      cin >> x >> L;

      if (x == 1)
      {
        int result = MAX_PID;
        for (int l = L; l <= 100; ++l)
        {
          for (int g = 1; g <= 100; ++g)
          {
            if (problems[l][g].size() && result > *problems[l][g].begin())
            {
              result = *problems[l][g].begin();
            }
          }

          if (result != MAX_PID)
          {
            cout << result << '\n';
            break;
          }
        }

        if (result == MAX_PID)
          cout << -1 << '\n';
      }

      else if (x == -1)
      {
        int result = 0;
        for (int l = L - 1; l > 0; --l)
        {
          for (int g = 1; g <= 100; ++g)
          {
            if (problems[l][g].size() && result < *problems[l][g].rbegin())
            {
              result = *problems[l][g].rbegin();
            }
          }

          if (result)
          {
            cout << result << '\n';
            break;
          }
        }

        if (!result)
          cout << -1 << '\n';
      }
    }

    else if (command == "add")
    {
      int P, L, G;
      cin >> P >> L >> G;
      problems[L][G].insert(P);
      metadatas[P] = make_pair(L, G);
    }

    else if (command == "solved")
    {
      int P;
      cin >> P;
      int L = metadatas[P].first;
      int G = metadatas[P].second;
      metadatas[P] = make_pair(0, 0);
      problems[L][G].erase(P);
    }
  }

  return 0;
}
