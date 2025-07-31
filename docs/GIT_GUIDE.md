# 🧑‍💻 Git 사용 가이드 (ALSS 스터디)

이 문서는 알고리즘 스터디 참여자들이 Git을 통해 소스 코드를 공유하고 관리하는 방법을 안내합니다.

---

## 📌 전체 워크플로우

1. **관리자**가 주차별 폴더 구조를 생성합니다.  
   예: `week01/boj_1000/`

2. 각자 `main` 브랜치를 최신화합니다.

   ```bash
   git checkout main
   git pull origin main
   ```

3. 새로운 브랜치를 생성합니다.

   * 브랜치 이름 규칙: `week{주차번호}-{이름}`
     예: `week01-keehoon`

   ```bash
   git checkout -b week01-keehoon
   ```

4. 자신의 커밋에 **소스 코드 파일만 추가**합니다.

   * 파일명: `{이름}.{확장자}` (예: `keehoon.cpp`, `youngjae.py`)
   * 여러 파일 제출 시: `이름_2.py`, `이름_3.java` 등으로 구분

5. 원격 브랜치에 푸시합니다.

   ```bash
   git add .
   git commit -m "풀이 추가"
   git push origin week01-keehoon
   ```

6. GitHub에서 Pull Request(PR)을 생성합니다.

   * PR 제목 규칙:

     ``` PR
     :page_facing_up: submit: week{주차번호}-{이름}
     ```

     예: `:page_facing_up: submit: week01-keehoon`

   * **커밋 메시지는 자유롭게 작성**하셔도 됩니다.
     → squash merge를 사용할 예정입니다.

7. **PR 승인 후 브랜치는 삭제합니다.**

---

## 📄 PR 템플릿 안내

PR을 생성하면 자동으로 템플릿이 적용됩니다.
다음 항목을 포함해 주세요:

* 문제 정보 (주차, 플랫폼, 경로 등)
* 풀이 요약 (알고리즘/로직/어려웠던 점 등)
* 리뷰 요청 포인트 (선택 사항)
* 체크리스트 (PR 제목, 파일명 등)

👉 PR 제목 형식:
`:page_facing_up: submit: week01-keehoon`

---

## 📝 이슈 템플릿 안내

이슈를 통해 다음과 같은 내용을 자유롭게 등록할 수 있습니다:

* ❓ **질문하기**: Git, PR, 문제 풀이, 규칙 등 궁금한 점
* 💡 **건의사항 제출**: 일정 조정, 운영 개선, 규칙 제안 등

> 이슈 작성 시 템플릿이 자동 적용됩니다.
> 자유롭게 등록하고, 관리자는 빠르게 확인할 예정입니다.

---

## 📂 디렉토리 구조 예시

```bash
week01/
├── boj_1000/
│   ├── keehoon.cpp
│   ├── youngjae.py
│   └── youngjae_2.py
└── README.md
```

---

## 📎 기타 사항

* **빈 폴더는 Git에 반영되지 않습니다.**
  필요한 경우 `.gitkeep` 파일을 임시로 추가할 수 있습니다.

* 문제나 충돌이 발생하거나 문의사항이 있다면,
  **언제든지 관리자에게 연락해주세요.**

---

감사합니다 🙌
