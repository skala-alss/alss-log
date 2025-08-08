# ⚙️ BOJ 문제 자동 세팅 스크립트 사용 가이드

이 문서는 알고리즘 스터디에서 사용하는 `init-boj.sh` 스크립트의 설치 및 사용법을 안내합니다.
해당 스크립트를 통해 **BOJ 문제 번호 기반으로 자동 폴더 세팅 및 코드 템플릿을 생성**할 수 있습니다.

---

## 📦 사전 설치 항목

| 언어         | 필요 환경 구성                                      |
| ---------- | --------------------------------------------- |
| **C++**    | [MSYS2](https://www.msys2.org/) + `ucrt64` 환경 |
| **Python** | Python 3.XX 버전 설치                             |
| **Java**   | OpenJDK 11\~17 버전 설치                          |
| **공통**     | Git Bash 설치 (Windows 사용자 기준)                  |

---

## 📁 설치 및 초기 설정

1. 홈 디렉토리에 `.scripts` 폴더를 생성합니다.
   예: `C:/Users/USERNAME/.scripts/`

2. `init-boj.sh` 파일을 해당 `.scripts` 폴더에 복사합니다.

3. 실행 권한 부여 (Git Bash 기준):

   ```bash
   chmod +x ~/.scripts/init-boj.sh
   ```

4. 시스템 환경변수에 `.scripts` 경로를 등록합니다.

   * Windows: 시스템 환경 변수 → `PATH`에 `.scripts` 경로 추가

5. 이제 **어느 디렉토리에서든 `init-boj.sh`를 실행할 수 있습니다.**

---

## 🚀 사용법

1. 문제 디렉토리로 이동합니다.
   디렉토리명은 반드시 다음과 같은 형식을 따라야 합니다:

   ```file
   boj_문제번호_제목
   예: boj_1000_A+B
   ```

2. 아래 명령어 중 하나를 실행합니다:

   ```bash
   init-boj.sh cpp    # C++
   init-boj.sh py     # Python
   init-boj.sh java   # Java
   ```

3. 아래 항목이 자동으로 생성됩니다:

   * `이름_문제번호.확장자` (언어별 코드 스니펫 포함)
   * `input.txt` (예제 입력 자동 수집)
   * `build.sh` (C++의 경우 컴파일 스크립트)
   * `.vscode/` 설정 (C++ 한정)

---

## ⚠️ 주의사항

* **Java**: 클래스 이름은 파일명과 동일해야 합니다 (`이름_문제번호.java`).
  → 백준 제출 시 `class Main`으로 이름을 바꿔 제출해야 합니다.

* **C++**: Git Bash 또는 MSYS2의 `ucrt64` 환경에서 실행해야 하며,
  `./build.sh`를 통해 컴파일 및 실행합니다.

* **파싱 오류나 환경 문제 발생 시**, 관리자에게 문의하세요.

---

## ✅ 예시 실행 흐름

```bash
cd ~/Desktop/alss-log/week01/boj_1000_A+B/
init-boj.sh cpp
```

```bash
# 생성된 파일 목록
- keehoon_1000.cpp
- input.txt
- build.sh
- .vscode/...
```

```bash
# C++ 실행 (ucrt 터미널에서)
./build.sh
```

---

📬 문의: GitHub 이슈 또는 슬랙/노션을 통해 관리자에게 연락 바랍니다.
