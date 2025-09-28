# 🗓️ Week 09 – 문제 목록 (최단경로 · 0-1 BFS · 분리집합 · MST)

9주차는 **최단경로 알고리즘**(다익스트라·벨만–포드·플로이드–워셜)을 중심으로 **0-1 BFS**, **분리 집합(Union-Find)**, **최소 스패닝 트리(MST)** 를 다룹니다.

**목표**

* **최단경로(다익스트라/벨만–포드/플로이드–워셜)**: 팀 전원 **올솔(All Solve)**
* **0-1 BFS · 분리 집합 · MST**: 각자 **2문제 이상**
* 풀이 후 **PR 제출** → **서로 리뷰(질문/칭찬/개선 제안)**

---

## 🚦 다익스트라

<!--START:PROGRESS:DIJKSTRA-->

|                               솔브드 티어                               |   번호  | 제목              |                      링크                     |                   폴더                   | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | :---: | :-------------- | :-----------------------------------------: | :------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 18352 | 특정 거리의 도시 찾기    | [🔗](https://www.acmicpc.net/problem/18352) |  [📁](./다익스트라/boj_18352_특정_거리의_도시_찾기)  |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> |  1446 | 지름길             |  [🔗](https://www.acmicpc.net/problem/1446) |       [📁](./다익스트라/boj_1446_지름길)       |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> |  1916 | 최소비용 구하기        |  [🔗](https://www.acmicpc.net/problem/1916) |     [📁](./다익스트라/boj_1916_최소비용_구하기)    |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> |  4485 | 녹색 옷 입은 애가 젤다지? |  [🔗](https://www.acmicpc.net/problem/4485) | [📁](./다익스트라/boj_4485_녹색_옷_입은_애가_젤다지？) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/14.svg" width="20"/> | 22955 | 고양이 도도의 탈출기     | [🔗](https://www.acmicpc.net/problem/22955) |   [📁](./다익스트라/boj_22955_고양이_도도의_탈출기)  |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |

<!--END:PROGRESS:DIJKSTRA-->

---

## ⏱️ 벨만‑포드

<!--START:PROGRESS:BELLMAN_FORD-->

|                               솔브드 티어                               |   번호  | 제목      |                      링크                     |                폴더               | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | :---: | :------ | :-----------------------------------------: | :-----------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 11657 | 타임머신    | [🔗](https://www.acmicpc.net/problem/11657) |   [📁](./벨만-포드/boj_11657_타임머신)  |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> |  1865 | 웜홀      |  [🔗](https://www.acmicpc.net/problem/1865) |    [📁](./벨만-포드/boj_1865_웜홀)    |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 13317 | 한 번 남았다 | [🔗](https://www.acmicpc.net/problem/13317) | [📁](./벨만-포드/boj_13317_한_번_남았다) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/15.svg" width="20"/> |  1738 | 골목길     |  [🔗](https://www.acmicpc.net/problem/1738) |    [📁](./벨만-포드/boj_1738_골목길)   |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/16.svg" width="20"/> |  1219 | 오민식의 고민 |  [🔗](https://www.acmicpc.net/problem/1219) |  [📁](./벨만-포드/boj_1219_오민식의_고민) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |

<!--END:PROGRESS:BELLMAN_FORD-->

---

## 🌐 플로이드‑워셜

<!--START:PROGRESS:FLOYD_WARSHALL-->

|                               솔브드 티어                               |   번호  | 제목             |                      링크                     |                    폴더                   | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | :---: | :------------- | :-----------------------------------------: | :-------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> |  1058 | 친구             |  [🔗](https://www.acmicpc.net/problem/1058) |       [📁](./플로이드-워셜/boj_1058_친구)       |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> |  1389 | 케빈 베이컨의 6단계 법칙 |  [🔗](https://www.acmicpc.net/problem/1389) | [📁](./플로이드-워셜/boj_1389_케빈_베이컨의_6단계_법칙) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 11403 | 경로 찾기          | [🔗](https://www.acmicpc.net/problem/11403) |     [📁](./플로이드-워셜/boj_11403_경로_찾기)     |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> |  2660 | 회장뽑기           |  [🔗](https://www.acmicpc.net/problem/2660) |      [📁](./플로이드-워셜/boj_2660_회장뽑기)      |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 11404 | 플로이드           | [🔗](https://www.acmicpc.net/problem/11404) |      [📁](./플로이드-워셜/boj_11404_플로이드)     |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |

<!--END:PROGRESS:FLOYD_WARSHALL-->

---

## 🧮 0‑1 BFS

<!--START:PROGRESS:ZERO_ONE_BFS-->

|                               솔브드 티어                               |   번호  | 제목       |                      링크                     |                   폴더                   | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | :---: | :------- | :-----------------------------------------: | :------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 13549 | 숨바꼭질 3   | [🔗](https://www.acmicpc.net/problem/13549) |    [📁](./0-1_BFS/boj_13549_숨바꼭질_3)    |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> |  1584 | 게임       |  [🔗](https://www.acmicpc.net/problem/1584) |       [📁](./0-1_BFS/boj_1584_게임)      |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> |  1261 | 알고스팟     |  [🔗](https://www.acmicpc.net/problem/1261) |      [📁](./0-1_BFS/boj_1261_알고스팟)     |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> |  2665 | 미로만들기    |  [🔗](https://www.acmicpc.net/problem/2665) |     [📁](./0-1_BFS/boj_2665_미로만들기)     |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 14497 | 주난의 난(難) | [🔗](https://www.acmicpc.net/problem/14497) | [📁](./0-1_BFS/boj_14497_주난의_난%28難%29) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |

<!--END:PROGRESS:ZERO_ONE_BFS-->

---

## 🔗 분리 집합 (Union‑Find)

<!--START:PROGRESS:UNION_FIND-->

|                               솔브드 티어                               |   번호  | 제목                  |                      링크                     |                      폴더                     | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | :---: | :------------------ | :-----------------------------------------: | :-----------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 24542 | 튜터-튜티 관계의 수         | [🔗](https://www.acmicpc.net/problem/24542) |     [📁](./분리_집합/boj_24542_튜터-튜티_관계의_수)     |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> |  1717 | 집합의 표현              |  [🔗](https://www.acmicpc.net/problem/1717) |        [📁](./분리_집합/boj_1717_집합의_표현)        |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 17352 | 여러분의 다리가 되어 드리겠습니다! | [🔗](https://www.acmicpc.net/problem/17352) | [📁](./분리_집합/boj_17352_여러분의_다리가_되어_드리겠습니다!) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> |  1976 | 여행 가자               |  [🔗](https://www.acmicpc.net/problem/1976) |         [📁](./분리_집합/boj_1976_여행_가자)        |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 17619 | 개구리 점프              | [🔗](https://www.acmicpc.net/problem/17619) |        [📁](./분리_집합/boj_17619_개구리_점프)       |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |

<!--END:PROGRESS:UNION_FIND-->

---

## 🕸️ 최소 스패닝 트리 (MST)

<!--START:PROGRESS:MST-->

|                               솔브드 티어                               |  번호  | 제목        |                     링크                     |                  폴더                  | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | :--: | :-------- | :----------------------------------------: | :----------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 1197 | 최소 스패닝 트리 | [🔗](https://www.acmicpc.net/problem/1197) | [📁](./최소_스패닝_트리/boj_1197_최소_스패닝_트리) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 1922 | 네트워크 연결   | [🔗](https://www.acmicpc.net/problem/1922) |  [📁](./최소_스패닝_트리/boj_1922_네트워크_연결)  |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 1647 | 도시 분할 계획  | [🔗](https://www.acmicpc.net/problem/1647) |  [📁](./최소_스패닝_트리/boj_1647_도시_분할_계획) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 4386 | 별자리 만들기   | [🔗](https://www.acmicpc.net/problem/4386) |  [📁](./최소_스패닝_트리/boj_4386_별자리_만들기)  |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 1774 | 우주신과의 교감  | [🔗](https://www.acmicpc.net/problem/1774) |  [📁](./최소_스패닝_트리/boj_1774_우주신과의_교감) |                                    ❌                                    |                              ❌                              |                                ❌                                |                                      ❌                                      |                                   ❌                                   |                                  ❌                                  |

<!--END:PROGRESS:MST-->

---

> **Legend**
> #1 = nOOne-is-hier · #2 = SDGeo12 · #3 = jiyunee02 · #4 = skala-changhyun · #5 = seo-youngjae · #6 = JinYeopKang

---

## 📝 학습 자료

* [📄 Week 09 학습 노트 (PDF)](../../docs/study-note-week09.pdf)

---

## ✅ 제출 규칙 요약

| 항목    | 규칙                                     |
| ----- | -------------------------------------- |
| 브랜치명  | `week09-{이름}`                          |
| 파일명   | `{이름}.확장자` (여러 파일 시 `_2`, `_3`)        |
| PR 제목 | `:page_facing_up: submit: week09-{이름}` |
| 비고    | 경로명: 띄어쓰기→`_`, 금지문자→전각(예: `?→？`)       |

---

## 💬 코드 리뷰 참여

1. 다른 팀원의 PR을 열어 코드 흐름을 읽습니다.
2. **질문·칭찬·개선 제안**을 코멘트로 남깁니다.
3. 서로의 관점을 공유하며 더 좋은 풀이를 만들어 봅시다! 🚀
