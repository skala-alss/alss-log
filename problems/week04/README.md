# 🗓️ Week 04 – 문제 목록 (완전탐색·재귀·분할정복·백트래킹)

4주차는 \*\*완전탐색(Brute Force)·재귀(Recursion)·분할정복(Divide & Conquer)·백트래킹(Backtracking)\*\*을 다룹니다.
**목표**는 다음과 같습니다.

* **브루트포스&재귀&백트래킹 – 초급(골드 미만)**: 팀 전원 **올솔(All Solve)** 도전
* **브루트포스&재귀&백트래킹 – 고급(골드 이상)**: 각자 **최소 1문제 이상**
* **분할 정복**: 각자 **골드 이상 최소 1문제 이상**

> **Tip**
> 제출 여부·리뷰 상태는 GitHub PR과 백준 그룹에서 확인해 주세요.
> ▸ 문제를 풀었으면 **PR 제출** 후 **다른 팀원의 코드를 꼭 리뷰**해 주세요.

---

## 🧩 브루트포스&재귀&백트래킹—초급(골드 미만)

> **비고**: `솔브드 티어`는 solved.ac 기준

<!--START:PROGRESS:BEGINNER-->

| 솔브드 티어 | 번호 | 제목 | 링크 | 폴더 | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
|:---:|---:|:---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| <img src="https://static.solved.ac/tier_small/1.svg" alt="Bronze V" width="20"/> | 27433 | 팩토리얼 2 | [🔗](https://www.acmicpc.net/problem/27433) | [📁](./브루트포스&재귀&백트래킹-초급/boj_27433_팩토리얼_2) | ✅ | ✅ | ❌ | ✅ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/1.svg" alt="Bronze V" width="20"/> | 27434 | 팩토리얼 3 | [🔗](https://www.acmicpc.net/problem/27434) | [📁](./브루트포스&재귀&백트래킹-초급/boj_27434_팩토리얼_3) | ✅ | ✅ | ❌ | ✅ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/7.svg" alt="Silver IV" width="20"/> | 1065 | 한수 | [🔗](https://www.acmicpc.net/problem/1065) | [📁](./브루트포스&재귀&백트래킹-초급/boj_1065_한수) | ✅ | ☑️ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15649 | N과 M (1) | [🔗](https://www.acmicpc.net/problem/15649) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15649_N과_M_(1)) | ✅ | ❌ | ❌ | ✅ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15650 | N과 M (2) | [🔗](https://www.acmicpc.net/problem/15650) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15650_N과_M_(2)) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15651 | N과 M (3) | [🔗](https://www.acmicpc.net/problem/15651) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15651_N과_M_(3)) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15652 | N과 M (4) | [🔗](https://www.acmicpc.net/problem/15652) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15652_N과_M_(4)) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15654 | N과 M (5) | [🔗](https://www.acmicpc.net/problem/15654) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15654_N과_M_(5)) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15655 | N과 M (6) | [🔗](https://www.acmicpc.net/problem/15655) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15655_N과_M_(6)) | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15656 | N과 M (7) | [🔗](https://www.acmicpc.net/problem/15656) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15656_N과_M_(7)) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 15657 | N과 M (8) | [🔗](https://www.acmicpc.net/problem/15657) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15657_N과_M_(8)) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 15663 | N과 M (9) | [🔗](https://www.acmicpc.net/problem/15663) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15663_N과_M_(9)) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 15664 | N과 M (10) | [🔗](https://www.acmicpc.net/problem/15664) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15664_N과_M_(10)) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 15665 | N과 M (11) | [🔗](https://www.acmicpc.net/problem/15665) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15665_N과_M_(11)) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 15666 | N과 M (12) | [🔗](https://www.acmicpc.net/problem/15666) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15666_N과_M_(12)) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 15658 | 연산자 끼워넣기 (2) | [🔗](https://www.acmicpc.net/problem/15658) | [📁](./브루트포스&재귀&백트래킹-초급/boj_15658_연산자_끼워넣기_(2)) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" alt="Silver I" width="20"/> | 14888 | 연산자 끼워넣기 | [🔗](https://www.acmicpc.net/problem/14888) | [📁](./브루트포스&재귀&백트래킹-초급/boj_14888_연산자_끼워넣기) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" alt="Silver I" width="20"/> | 12348 | 분해합 2 | [🔗](https://www.acmicpc.net/problem/12348) | [📁](./브루트포스&재귀&백트래킹-초급/boj_12348_분해합_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" alt="Silver I" width="20"/> | 11277 | 2-SAT - 1 | [🔗](https://www.acmicpc.net/problem/11277) | [📁](./브루트포스&재귀&백트래킹-초급/boj_11277_2-SAT_-_1) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" alt="Silver I" width="20"/> | 11278 | 2-SAT - 2 | [🔗](https://www.acmicpc.net/problem/11278) | [📁](./브루트포스&재귀&백트래킹-초급/boj_11278_2-SAT_-_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:BEGINNER-->

---

## 🧠 브루트포스 & 재귀 & 백트래킹 — 고급(골드 이상)

<!--START:PROGRESS:ADVANCED-->

| 솔브드 티어 | 번호 | 제목 | 링크 | 폴더 | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
|:---:|---:|:---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| <img src="https://static.solved.ac/tier_small/11.svg" alt="Gold V" width="20"/> | 12347 | 한수 2 | [🔗](https://www.acmicpc.net/problem/12347) | [📁](./브루트포스&재귀&백트래킹-고급/boj_12347_한수_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" alt="Gold IV" width="20"/> | 9663 | N-Queen | [🔗](https://www.acmicpc.net/problem/9663) | [📁](./브루트포스&재귀&백트래킹-고급/boj_9663_N_Queen) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" alt="Gold IV" width="20"/> | 14502 | 연구소 | [🔗](https://www.acmicpc.net/problem/14502) | [📁](./브루트포스&재귀&백트래킹-고급/boj_14502_연구소) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" alt="Gold IV" width="20"/> | 15659 | 연산자 끼워넣기 (3) | [🔗](https://www.acmicpc.net/problem/15659) | [📁](./브루트포스&재귀&백트래킹-고급/boj_15659_연산자_끼워넣기_(3)) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" alt="Gold IV" width="20"/> | 17141 | 연구소 2 | [🔗](https://www.acmicpc.net/problem/17141) | [📁](./브루트포스&재귀&백트래킹-고급/boj_17141_연구소_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" alt="Gold III" width="20"/> | 17142 | 연구소 3 | [🔗](https://www.acmicpc.net/problem/17142) | [📁](./브루트포스&재귀&백트래킹-고급/boj_17142_연구소_3) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" alt="Gold III" width="20"/> | 16637 | 괄호 추가하기 | [🔗](https://www.acmicpc.net/problem/16637) | [📁](./브루트포스&재귀&백트래킹-고급/boj_16637_괄호_추가하기) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" alt="Gold III" width="20"/> | 17471 | 게리맨더링 | [🔗](https://www.acmicpc.net/problem/17471) | [📁](./브루트포스&재귀&백트래킹-고급/boj_17471_게리맨더링) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" alt="Gold II" width="20"/> | 17779 | 게리맨더링 2 | [🔗](https://www.acmicpc.net/problem/17779) | [📁](./브루트포스&재귀&백트래킹-고급/boj_17779_게리맨더링_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/13.svg" alt="Gold III" width="20"/> | 30242 | N-Queen (Easy) | [🔗](https://www.acmicpc.net/problem/30242) | [📁](./브루트포스&재귀&백트래킹-고급/boj_30242_N_Queen_(Easy)) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" alt="Gold II" width="20"/> | 27439 | 팩토리얼 4 | [🔗](https://www.acmicpc.net/problem/27439) | [📁](./브루트포스&재귀&백트래킹-고급/boj_27439_팩토리얼_4) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" alt="Gold II" width="20"/> | 16639 | 괄호 추가하기 3 | [🔗](https://www.acmicpc.net/problem/16639) | [📁](./브루트포스&재귀&백트래킹-고급/boj_16639_괄호_추가하기_3) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/15.svg" alt="Gold I" width="20"/> | 16638 | 괄호 추가하기 2 | [🔗](https://www.acmicpc.net/problem/16638) | [📁](./브루트포스&재귀&백트래킹-고급/boj_16638_괄호_추가하기_2) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:ADVANCED-->

---

## 🪚 분할 정복 (Divide & Conquer)

<!--START:PROGRESS:DNC-->

| 솔브드 티어 | 번호 | 제목 | 링크 | 폴더 | <a href="https://github.com/nOOne-is-hier" title="nOOne-is-hier">#1</a> | <a href="https://github.com/SDGeo12" title="SDGeo12">#2</a> | <a href="https://github.com/jiyunee02" title="jiyunee02">#3</a> | <a href="https://github.com/skala-changhyun" title="skala-changhyun">#4</a> | <a href="https://github.com/seo-youngjae" title="seo-youngjae">#5</a> | <a href="https://github.com/JinYeopKang" title="JinYeopKang">#6</a> |
|:---:|---:|:---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| <img src="https://static.solved.ac/tier_small/8.svg" alt="Silver III" width="20"/> | 4779 | 칸토어 집합 | [🔗](https://www.acmicpc.net/problem/4779) | [📁](./분할정복/boj_4779_칸토어_집합) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 1780 | 종이의 개수 | [🔗](https://www.acmicpc.net/problem/1780) | [📁](./분할정복/boj_1780_종이의_개수) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/9.svg" alt="Silver II" width="20"/> | 2630 | 색종이 만들기 | [🔗](https://www.acmicpc.net/problem/2630) | [📁](./분할정복/boj_2630_색종이_만들기) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" alt="Silver I" width="20"/> | 1992 | 쿼드트리 | [🔗](https://www.acmicpc.net/problem/1992) | [📁](./분할정복/boj_1992_쿼드트리) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/10.svg" alt="Silver I" width="20"/> | 1629 | 곱셈 | [🔗](https://www.acmicpc.net/problem/1629) | [📁](./분할정복/boj_1629_곱셈) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/11.svg" alt="Gold V" width="20"/> | 2447 | 별 찍기 - 10 | [🔗](https://www.acmicpc.net/problem/2447) | [📁](./분할정복/boj_2447_별_찍기_10) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/11.svg" alt="Gold V" width="20"/> | 1074 | Z | [🔗](https://www.acmicpc.net/problem/1074) | [📁](./분할정복/boj_1074_Z) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/12.svg" alt="Gold IV" width="20"/> | 10830 | 행렬 제곱 | [🔗](https://www.acmicpc.net/problem/10830) | [📁](./분할정복/boj_10830_행렬_제곱) | ☑️ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" alt="Gold II" width="20"/> | 11444 | 피보나치 수 6 | [🔗](https://www.acmicpc.net/problem/11444) | [📁](./분할정복/boj_11444_피보나치_수_6) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| <img src="https://static.solved.ac/tier_small/14.svg" alt="Gold II" width="20"/> | 2749 | 피보나치 수 3 | [🔗](https://www.acmicpc.net/problem/2749) | [📁](./분할정복/boj_2749_피보나치_수_3) | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

<!--END:PROGRESS:DNC-->

> **Legend**  
> #1 = nOOne-is-hier  
> #2 = SDGeo12  
> #3 = jiyunee02  
> #4 = skala-changhyun  
> #5 = seo-youngjae  
> #6 = JinYeopKang
---

## 📝 학습 자료

* [📄 Week 04 학습 노트 (PDF)](../../docs/study-note-week04.pdf)

---

## ✅ 제출 규칙 요약

| 항목     | 규칙                                     |
| ------ | -------------------------------------- |
| 브랜치명   | `week04-{이름}`                          |
| 파일명    | `{이름}.확장자` (여러 파일 제출 시 `_2`, `_3` 붙이기) |
| PR 제목  | `:page_facing_up: submit: week04-{이름}` |
| PR 템플릿 | 자동 적용 – 문제 정보·풀이 요약·체크리스트 작성           |

---

## 💬 코드 리뷰 참여

1. 다른 팀원의 PR을 열어 코드 흐름을 읽어봅니다.
2. **질문·칭찬·개선 제안**을 코멘트로 남깁니다.
3. 서로의 관점을 공유하며 더 나은 풀이를 탐구해 봅시다! 🚀

---

### 운영 메모

* `솔브드 티어`는 이후 **자동 수집 스크립트**로 업데이트 예정입니다.
* `@member1~6`은 실제 GitHub 핸들로 교체해 주세요(예: `@keo-dev`).
* 카테고리 폴더 구조는 위 링크 경로를 기준으로 생성하세요.

<!--WEEKMETA: released_at=2025-08-21T00:00:00+09:00; deadline= -->
