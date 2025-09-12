# 🗓️ Week 06 – 문제 목록 (슬라이딩 윈도우·투 포인터 / 이분 탐색·파라메트릭 서치)

6주차는 **슬라이딩 윈도우·투 포인터**와 **이분 탐색/파라메트릭 서치**를 핵심으로, **삼분탐색/중간에서** **만나기**(**MITM**)까지 확장합니다.

**목표**

* 슬라이딩 윈도우·투 포인터: 팀 전원 **올솔(All Solve)**
* 이분 탐색/파라메트릭 서치: 각자 **올솔(All Solve)**
* 고급·삼분탐색/MITM: 각자 **1문제 도전**

> **Tip**
> 제출·리뷰 현황은 GitHub PR과 백준 그룹에서 확인하세요.
> ▸ 풀이 후 **PR 제출** → **다른 팀원 코드 리뷰(질문/칭찬/개선 제안)**

---

## 🔁 슬라이딩 윈도우 / 투 포인터

<!--START:PROGRESS:SLIDING_TWO_POINTER-->

|                               솔브드 티어                               |    번호 | 제목             |                      링크                     |                        폴더                       | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | ----: | :------------- | :-----------------------------------------: | :---------------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/7.svg"  width="20"/> | 1940 | 주몽 | [🔗](https://www.acmicpc.net/problem/1940) | [📁](./슬라이딩_윈도우&투_포인터/boj_1940_주몽) | ✅ | ✅ | ✅ | ✅ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg"  width="20"/> | 2559 | 수열 | [🔗](https://www.acmicpc.net/problem/2559) | [📁](./슬라이딩_윈도우&투_포인터/boj_2559_수열) | ✅ | ❌ | ✅ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg"  width="20"/> | 12847 | 꿀 아르바이트 | [🔗](https://www.acmicpc.net/problem/12847) | [📁](./슬라이딩_윈도우&투_포인터/boj_12847_꿀_아르바이트) | ✅ | ❌ | ✅ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg"  width="20"/> | 10025 | 게으른 백곰 | [🔗](https://www.acmicpc.net/problem/10025) | [📁](./슬라이딩_윈도우&투_포인터/boj_10025_게으른_백곰) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg"  width="20"/> | 21921 | 블로그 | [🔗](https://www.acmicpc.net/problem/21921) | [📁](./슬라이딩_윈도우&투_포인터/boj_21921_블로그) | ✅ | ❌ | ✅ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg"  width="20"/> | 27496 | 발머의 피크 이론 | [🔗](https://www.acmicpc.net/problem/27496) | [📁](./슬라이딩_윈도우&투_포인터/boj_27496_발머의_피크_이론) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 12891 | DNA 비밀번호 | [🔗](https://www.acmicpc.net/problem/12891) | [📁](./슬라이딩_윈도우&투_포인터/boj_12891_DNA_비밀번호) | ✅ | ❌ | ✅ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 14465 | 소가 길을 건너간 이유 5 | [🔗](https://www.acmicpc.net/problem/14465) | [📁](./슬라이딩_윈도우&투_포인터/boj_14465_소가_길을_건너간_이유_5) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 2531 | 회전 초밥 | [🔗](https://www.acmicpc.net/problem/2531) | [📁](./슬라이딩_윈도우&투_포인터/boj_2531_회전_초밥) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 15565 | 귀여운 라이언 | [🔗](https://www.acmicpc.net/problem/15565) | [📁](./슬라이딩_윈도우&투_포인터/boj_15565_귀여운_라이언) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:SLIDING_TWO_POINTER-->

---

## 🔎 이분 탐색 / 파라메트릭 서치

<!--START:PROGRESS:BINARY_SEARCH-->

|                               솔브드 티어                               |    번호 | 제목        |                      링크                     |                     폴더                     | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | ----: | :-------- | :-----------------------------------------: | :----------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 1654 | 랜선 자르기 | [🔗](https://www.acmicpc.net/problem/1654) | [📁](./이분_탐색&파라메트릭_서치/boj_1654_랜선_자르기) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 2512 | 예산 | [🔗](https://www.acmicpc.net/problem/2512) | [📁](./이분_탐색&파라메트릭_서치/boj_2512_예산) | ✅ | ❌ | ❌ | ✅ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 2805 | 나무 자르기 | [🔗](https://www.acmicpc.net/problem/2805) | [📁](./이분_탐색&파라메트릭_서치/boj_2805_나무_자르기) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 13702 | 이상한 술집 | [🔗](https://www.acmicpc.net/problem/13702) | [📁](./이분_탐색&파라메트릭_서치/boj_13702_이상한_술집) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 14627 | 파닭파닭 | [🔗](https://www.acmicpc.net/problem/14627) | [📁](./이분_탐색&파라메트릭_서치/boj_14627_파닭파닭) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg"  width="20"/> | 16401 | 과자 나눠주기 | [🔗](https://www.acmicpc.net/problem/16401) | [📁](./이분_탐색&파라메트릭_서치/boj_16401_과자_나눠주기) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 2343 | 기타 레슨 | [🔗](https://www.acmicpc.net/problem/2343) | [📁](./이분_탐색&파라메트릭_서치/boj_2343_기타_레슨) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 2792 | 보석 상자 | [🔗](https://www.acmicpc.net/problem/2792) | [📁](./이분_탐색&파라메트릭_서치/boj_2792_보석_상자) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 6236 | 용돈 관리 | [🔗](https://www.acmicpc.net/problem/6236) | [📁](./이분_탐색&파라메트릭_서치/boj_6236_용돈_관리) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" width="20"/> | 16564 | 히오스 프로게이머 | [🔗](https://www.acmicpc.net/problem/16564) | [📁](./이분_탐색&파라메트릭_서치/boj_16564_히오스_프로게이머) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:BINARY_SEARCH-->

---

## 🧠 고급

<!--START:PROGRESS:ADVANCED-->

|                               솔브드 티어                               |    번호 | 제목                       |                      링크                     |                       폴더                      | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | ----: | :----------------------- | :-----------------------------------------: | :-------------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 2467 | 용액 | [🔗](https://www.acmicpc.net/problem/2467) | [📁](./고급/boj_2467_용액) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 2470 | 두 용액 | [🔗](https://www.acmicpc.net/problem/2470) | [📁](./고급/boj_2470_두_용액) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 3020 | 개똥벌레 | [🔗](https://www.acmicpc.net/problem/3020) | [📁](./고급/boj_3020_개똥벌레) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 3079 | 입국심사 | [🔗](https://www.acmicpc.net/problem/3079) | [📁](./고급/boj_3079_입국심사) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/11.svg" width="20"/> | 20437 | 문자열 게임 2 | [🔗](https://www.acmicpc.net/problem/20437) | [📁](./고급/boj_20437_문자열_게임_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 1253 | 좋다 | [🔗](https://www.acmicpc.net/problem/1253) | [📁](./고급/boj_1253_좋다) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 1806 | 부분합 | [🔗](https://www.acmicpc.net/problem/1806) | [📁](./고급/boj_1806_부분합) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 2110 | 공유기 설치 | [🔗](https://www.acmicpc.net/problem/2110) | [📁](./고급/boj_2110_공유기_설치) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 2539 | 모자이크 | [🔗](https://www.acmicpc.net/problem/2539) | [📁](./고급/boj_2539_모자이크) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 3078 | 좋은 친구 | [🔗](https://www.acmicpc.net/problem/3078) | [📁](./고급/boj_3078_좋은_친구) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 15961 | 회전 초밥 | [🔗](https://www.acmicpc.net/problem/15961) | [📁](./고급/boj_15961_회전_초밥) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 1644 | 소수의 연속합 | [🔗](https://www.acmicpc.net/problem/1644) | [📁](./고급/boj_1644_소수의_연속합) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 2473 | 세 용액 | [🔗](https://www.acmicpc.net/problem/2473) | [📁](./고급/boj_2473_세_용액) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 17951 | 흩날리는 시험지 속에서 내 평점이 느껴진거야 | [🔗](https://www.acmicpc.net/problem/17951) | [📁](./고급/boj_17951_흩날리는_시험지_속에서_내_평점이_느껴진거야) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" width="20"/> | 2352 | 반도체 설계 | [🔗](https://www.acmicpc.net/problem/2352) | [📁](./고급/boj_2352_반도체_설계) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/15.svg" width="20"/> | 1561 | 놀이 공원 | [🔗](https://www.acmicpc.net/problem/1561) | [📁](./고급/boj_1561_놀이_공원) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:ADVANCED-->

---

## 🔺 삼분탐색 / 중간에서 만나기 (MITM)

<!--START:PROGRESS:TERNARY_MITM-->

|                               솔브드 티어                               |    번호 | 제목         |                      링크                     |                     폴더                     | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
| :----------------------------------------------------------------: | ----: | :--------- | :-----------------------------------------: | :----------------------------------------: | :---------------------------------------------------------------------: | :---------------------------------------------------------: | :-------------------------------------------------------------: | :-------------------------------------------------------------------------: | :-------------------------------------------------------------------: | :-----------------------------------------------------------------: |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 2295 | 세 수의 합 | [🔗](https://www.acmicpc.net/problem/2295) | [📁](./삼분_탐색&중간에서_만나기/boj_2295_세_수의_합) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 11662 | 민호와 강호 | [🔗](https://www.acmicpc.net/problem/11662) | [📁](./삼분_탐색&중간에서_만나기/boj_11662_민호와_강호) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" width="20"/> | 11664 | 선분과 점 | [🔗](https://www.acmicpc.net/problem/11664) | [📁](./삼분_탐색&중간에서_만나기/boj_11664_선분과_점) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" width="20"/> | 9998 | 블록 쌓기 | [🔗](https://www.acmicpc.net/problem/9998) | [📁](./삼분_탐색&중간에서_만나기/boj_9998_블록_쌓기) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" width="20"/> | 7453 | 합이 0인 네 정수 | [🔗](https://www.acmicpc.net/problem/7453) | [📁](./삼분_탐색&중간에서_만나기/boj_7453_합이_0인_네_정수) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/15.svg" width="20"/> | 1208 | 부분수열의 합 2 | [🔗](https://www.acmicpc.net/problem/1208) | [📁](./삼분_탐색&중간에서_만나기/boj_1208_부분수열의_합_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/15.svg" width="20"/> | 1450 | 냅색문제 | [🔗](https://www.acmicpc.net/problem/1450) | [📁](./삼분_탐색&중간에서_만나기/boj_1450_냅색문제) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/15.svg" width="20"/> | 32136 | 소신발언 | [🔗](https://www.acmicpc.net/problem/32136) | [📁](./삼분_탐색&중간에서_만나기/boj_32136_소신발언) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:TERNARY_MITM-->

---

> **Legend**
> \#1 = nOOne-is-hier · #2 = SDGeo12 · #3 = jiyunee02 · #4 = skala-changhyun · #5 = seo-youngjae · #6 = JinYeopKang

---

## 📝 학습 자료

* [📄 Week 06 학습 노트 (PDF)](../../docs/study-note-week06.pdf)

---

## ✅ 제출 규칙 요약

| 항목     | 규칙                                     |
| ------ | -------------------------------------- |
| 브랜치명   | `week06-{이름}`                          |
| 파일명    | `{이름}.확장자` (여러 파일 시 `_2`, `_3`)        |
| PR 제목  | `:page_facing_up: submit: week06-{이름}` |
| PR 템플릿 | 자동 적용 – 문제 정보·풀이 요약·체크리스트              |

---

## 💬 코드 리뷰 참여

1. 다른 팀원의 PR을 열어 코드 흐름을 읽습니다.
2. **질문·칭찬·개선 제안**을 코멘트로 남깁니다.
3. 서로의 관점을 공유하며 더 나은 풀이를 탐구해 봅시다! 🚀
