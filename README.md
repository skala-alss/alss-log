# <img width="101.2" height="25.85" alt="image" src="https://github.com/user-attachments/assets/e3f14879-c39e-4a9d-bf07-afc3baaaf47c" /> alss-log

SKALA 알고리즘 스터디 (ALSS)의 문제 풀이 기록 저장소입니다.  
팀원들이 주차별로 문제를 풀이하고, 코드 리뷰를 통해 함께 성장하는 것을 목표로 합니다.

---

## 🚩 스터디 목적

- 알고리즘 실력 향상 및 문제 해결 능력 강화
- 코드 리뷰를 통한 협업 및 커뮤니케이션 역량 향상
- Git 기반 협업 방식에 익숙해지기

---

## 📁 레포지토리 구조

```bash
alss-log/
├── week01/
│   ├── boj_1000/
│   │   ├── keehwon.cpp
│   │   └── youngjae.py
│   ├── programmers_12900/
│   └── README.md
├── docs/
│   ├── OT.pdf
│   ├── RULES.md
│   └── GIT_GUIDE.md
├── scripts/
│   ├── init-boj.sh
│   └── README.md
└── .github/
    ├── PULL_REQUEST_TEMPLATE.md
    └── ISSUE_TEMPLATE/
````

- `weekXX/`: 주차별 문제 풀이 코드 및 요약
- `docs/`: OT, 스터디 규칙, Git 가이드 등의 문서
- `.github/`: PR 템플릿 및 이슈 템플릿 설정

---

## 🧑‍💻 Git 사용 가이드

> PR은 **문제 풀이 코드 제출에만 사용**합니다.
> 그 외의 문서 작업, 리팩토링 등은 운영자가 직접 main 브랜치에 push합니다.

- 브랜치명: `week{주차번호}-{이름}`
  예: `week01-keehoon`
- PR 제목: `:page_facing_up: submit: week{주차번호}-{이름}`
  예: `:page_facing_up: submit: week01-keehoon`
- 파일명: `이름.확장자` (예: `keehwon.py`, `keehwon_2.cpp`)

📘 자세한 사용법은 👉 [Git 사용 가이드](./docs/GIT_GUIDE.md)

---

## 📌 스터디 규칙

- 성실하고 열정적으로 학습에 임합니다.
- 모든 문제 풀이가 의무는 아니며, 가능한 범위 내에서 도전합니다.
- 코드 리뷰는 질문과 칭찬을 함께 담아 서로를 성장시킵니다.
- PR 승인 후 브랜치는 삭제합니다.
- 일정이나 참여 관련 문의는 언제든 관리자에게 연락해주세요.

📃 규칙 전문 보기 👉 [스터디 운영 규칙](./docs/RULES.md)

---

## 📝 이슈 활용 안내

- ❓ 질문하기: Git/PR/문제 관련 궁금증
- 💡 건의사항 제출: 일정, 운영 방식, 규칙 제안 등

👉 이슈 생성 시 템플릿이 자동 적용됩니다.

---

## 🗂️ 학습 자료

| 주차      | 학습자료                                   | 문제 링크                 |
| ------- | -------------------------------------- | --------------------- |
| Week 01 | [📄 PDF](./docs/study-note-week01.pdf) | [📂 week01](./week01) |
| Week 02 | [📄 PDF](./docs/study-note-week02.pdf) | [📂 week01](./week02) |
| Week 04 | (예정)                                   | -                     |

---

## 🛠️ BOJ 문제 자동 세팅 도구

스터디에서는 BOJ 문제를 빠르게 세팅할 수 있는 Bash 스크립트 도구를 제공합니다.  
해당 스크립트를 사용하면 문제 번호 기반으로 자동으로 템플릿 코드, input.txt 등을 생성할 수 있습니다.

- 자동 생성 항목: `소스코드 스니펫`, `input.txt`, `build.sh(C++)`, `.vscode 설정(C++)`
- 언어별 지원: `C++`, `Python`, `Java`
- macOS / Windows 모두 사용 가능

📘 설치 및 사용법은 👉 [`scripts/README.md`](./scripts/README.md)

---

## ✨ 공식 문서 및 언어별 스타일 가이드

알고리즘 문제 풀이뿐 아니라, **실무 개발과 협업**, **기술 면접**, **장기적인 개발 습관 형성**에 있어  
공식 문서를 적극 활용하고, 언어별 코드 스타일을 익히는 것은 큰 도움이 됩니다.

📘 자세히 보기 👉 [STYLE_GUIDE.md](./docs/STYLE_GUIDE.md)

---

## 🙌 함께 성장하는 스터디

- 문제를 많이 푸는 것보다 **꾸준한 참여와 리뷰가 더 중요합니다.**
- 서로를 존중하며 자유롭게 소통하는 문화를 지향합니다.
- 모르는 것을 부끄러워하지 마세요. 질문이 바로 성장입니다.

---

📬 문의 및 건의: GitHub 이슈를 활용하거나, 슬랙/노션 등을 통해 관리자에게 알려주세요.
