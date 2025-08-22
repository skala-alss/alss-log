# ⚙️ BOJ 문제 자동 세팅 스크립트 (boj\_init.py)

**BOJ 문제 번호만 알면** 아래를 한 번에 자동으로 만들어줍니다.

* 언어별 **소스 템플릿** (파일 상단에 **solved.ac 메타** 주석 자동 삽입)
* **테스트 폴더** `tests/` 및 `sample*.in|.out`, 편의용 `input.txt`
* 언어 공통 **실행/채점 스크립트** `run.sh`
  → **소스 1개 선택 → `tests/*.in` 전부 실행 → 동일 이름의 `.out`와 비교**
* (C++ 전용) `.vscode/c_cpp_properties.json`

---

## 📦 요구 사항

### 1) Python & 패키지

* Python 3.8+
* 패키지 설치:

  ```bash
  pip install requests beautifulsoup4 lxml
  ```

  (윈도우에서 `lxml`이 안 깔리면 `pip install lxml-<버전>-cp<버전>-win_amd64.whl` 식의 **휠**을 설치하거나, `conda`/`pipx` 사용을 추천)

### 2) 각 언어 실행 환경

| 언어     | 필요 환경                                                   |
| ------ | ------------------------------------------------------- |
| C++    | **MSYS2** + **ucrt64** (Windows) / 시스템 g++(macOS/Linux) |
| Python | Python 3.x (UTF-8 권장)                                   |
| Java   | OpenJDK 11\~17 (javac, java)                            |

> Windows에서 C++은 `run.sh`가 **자동으로 UCRT64** 셸로 재시작(bounce)해서 빌드/실행합니다.
> 기본 경로는 `C:\msys64`로 가정합니다. 설치 경로가 다르면 `run.sh` 상단의 경로를 수정하세요.

### 3) Git Bash / 터미널

* Windows 사용자는 **Git Bash** 또는 MSYS2 터미널 권장
* macOS/Linux는 기본 터미널 사용

---

## 🛠️ 설치

**권장 위치**: `~/alss-log/scripts/boj_init.py` (아무 곳이나 가능)

PATH에 등록해서 어디서든 실행하고 싶다면:

* Windows (PowerShell):

  ```powershell
  setx PATH "$($env:PATH);C:\Users\<you>\.scripts"
  ```
  
* 등록 폴더에 `boj_init.py` 복사 후 실행 권한:

  ```bash
  chmod +x /path/to/boj_init.py
  ```

---

## 🚀 빠른 시작

### 1) 현재 폴더가 ‘문제 폴더’인 경우

폴더명이 아래 중 하나면 **자동으로 문제 번호를 인식**합니다.

* `boj_<id>_...`  예) `boj_17608_막대기`
* `<id>.<Title>`  예) `17608.막대기`
* `<id>_Title` / `<id>-Title`

```bash
# C++
python boj_init.py cpp
# Python
python boj_init.py py
# Java
python boj_init.py java
```

### 2) 폴더 밖에서 ‘지정 경로에’ 문제 폴더 생성 + 세팅

`--dest` / `--dest-base` / 환경변수 `BOJ_DEST_BASE`를 사용합니다.

```bash
# (권장) 기본 경로를 환경변수로 한 번만 지정
# Windows PowerShell
setx BOJ_DEST_BASE "C:\TIS\Baekjoon"
# macOS/Linux (bash/zsh)
export BOJ_DEST_BASE="$HOME/Desktop/TIS/Baekjoon"
```

이후:

```bash
# 기본 경로(BOJ_DEST_BASE) 바로 아래에 폴더 생성
python boj_init.py cpp --id 17608 --dest

# 기본 경로 뒤에 suffix 덧붙이기 (예: week02/스택)
python boj_init.py py --id 17608 --dest +week02/스택

# 기본 경로를 옵션으로 직접 지정 + suffix
python boj_init.py java --id 1006 --dest-base "C:/TIS/Baekjoon" --dest +week02/원형큐
```

> **지정경로 모드**에서는 폴더/파일명이 `<문제번호>.<제목_정제>` 로 생성됩니다.
> 예: `1006.습격자_초라기/1006.습격자_초라기.cpp` (또는 `.py`, `.java`)

---

## 🧩 생성 결과 & 파일명 규칙

* **일반 모드(현재 폴더):**
  `이름_문제번호.(cpp|py|java)` → `--username` 옵션으로 `이름` 지정 (기본: `keehoon`)
* **지정경로 모드:**
  `<문제번호>.<제목_정제>.(cpp|py|java)` (Java도 **파일명 그대로** 생성합니다)

생성 항목:

``` text
<소스파일>
tests/sample1.in
tests/sample1.out (있으면)
input.txt (샘플1 입력 복사)
run.sh
(언어가 C++일 때) .vscode/c_cpp_properties.json
```

**소스 템플릿의 입력 처리**

* 파이프/리다이렉션이 **없으면** `input.txt`를 자동으로 열어 읽도록 구성 (C++/Py/Java 모두 지원)
* `run.sh`로 실행할 때는 **항상 `tests/*.in`을 표준입력**으로 주입합니다.

---

## 🧪 테스트 & 채점 (`run.sh`)

```bash
# 인터랙티브 선택
./run.sh

# 특정 소스만 바로 실행
./run.sh "17608.막대기.cpp"
./run.sh "17608.막대기.py"
./run.sh "17608.막대기.java"
```

동작 순서:

1. 실행할 **소스 1개**를 고릅니다(인자 주면 바로 진행).
2. `tests/*.in`을 **모두 실행**해서 결과를 임시로 만든 뒤,
3. 같은 이름의 `tests/*.out`이 있으면 **정답 비교**합니다.

   * `diff -u`가 있으면 상세 비교
   * 없으면 `cmp -s`로 동등성만 체크(상세 diff 출력 불가)
4. 실행 결과는 `out/<소스파일>.<입력파일명>.out`으로 저장합니다.
5. CR/LF는 자동 정규화해서 비교합니다.

> **Windows + C++**: 현재 셸이 UCRT64가 아니면 `run.sh`가 **MSYS2 UCRT64 셸로 재시작**해서 컴파일/실행합니다.
> MSYS2 기본 설치 경로(`C:\msys64`)를 사용합니다. 경로가 다르면 `run.sh` 상단의
> `UCRT_BASH`, `UCRT_ENV` 값을 수정하세요.

---

## 🧾 옵션 일람 (boj\_init.py)

| 옵션                                 | 설명                                                                            |
| ---------------------------------- | ----------------------------------------------------------------------------- |
| `lang`                             | `cpp` / `py` / `java` (별칭: `c++`, `cpp17`, `python`)                          |
| `--id <n>`                         | 문제 번호 (없으면 폴더명에서 추출)                                                          |
| `--username <name>`                | 일반 모드 파일명 `이름_문제번호.*` 의 `이름` 값 (기본: `keehoon`)                                |
| `--run`                            | 생성 후 바로 `run.sh`로 해당 소스를 실행                                                   |
| `--no-solvedac`                    | solved.ac 조회 생략 (API 실패/속도 이슈시)                                               |
| `--max-tags <k>`                   | solved.ac 태그 최대 k개 (기본 8)                                                     |
| `--tier-emoji` / `--no-tier-emoji` | 티어 이모지 표시 on/off (기본 on)                                                      |
| `--debug`                          | HTTP 재시도 로그 출력                                                                |
| `--insecure`                       | HTTPS 인증서 검증 끄기 (임시 문제 해결용)                                                   |
| `--force` / `-f`                   | **기존 파일 덮어쓰기** (기본은 ‘건너뜀’)                                                    |
| `--dest`                           | 지정경로 모드 활성화. 값 생략 시 **기본 경로만** 사용. `+suffix`면 기본 경로 뒤에 덧붙임. 경로 문자열이면 그 경로 사용. |
| `--dest-base <path>`               | 지정경로 기본값. 없으면 환경변수 `BOJ_DEST_BASE`를 사용                                        |

### 환경 변수

* `BOJ_DEST_BASE` : `--dest` 기본 경로

  * 예) `C:\TIS\Baekjoon` 또는 `/Users/you/Desktop/TIS/Baekjoon`

---

## 🧠 작동 방식 (요약)

1. **BOJ 페이지 파싱**

   * 제목 / 시간 제한 / 메모리 제한
   * 샘플 입력/출력(`sample*.in|.out`) 수집 (개행/CR 정규화)
2. **solved.ac 메타 조회** (옵션)

   * 티어, 태그, 푼 사람 수, 평균 시도 → **소스 상단 주석으로 삽입**
3. **파일/폴더 구성**

   * 일반 모드 vs 지정경로 모드에 따라 파일명/폴더명 결정
   * 기존 파일 있으면 **건너뜀**, `--force`면 **덮어씀**
4. **추가 편의**

   * C++이면 VSCode 설정 파일 제공
   * VS Code 자동 실행 시도 (`code`/`code.cmd`)

---

## 🧩 테스트 케이스 직접 추가하기

* `tests/` 폴더 아래에 **원하는 이름의 `.in` 파일**을 추가하면 됩니다.

  * 예) `tests/mycase1.in`, `tests/edge_1.in`
* 정답 검증을 하려면 **같은 이름의 `.out`** 파일을 함께 두세요.

  * 예) `tests/mycase1.out`
* `run.sh`는 `tests/*.in`을 전부 실행하고, `.out`이 있으면 비교합니다.

---

## 💡 Java에 관해

* 템플릿은 **`class Main`** 기준입니다.

  * **로컬 실행:** `run.sh`가 `javac -encoding UTF-8 -d <tmp> <파일>` 후 `java -cp <tmp> Main`으로 실행
  * **제출:** `public class Main`으로 바꿔 제출하세요.
* `.class` 빌드 산출물은 임시 디렉터리를 사용하므로 작업 폴더에 남지 않습니다.

---

## 🧱 Windows & 인코딩 팁

* `run.sh`는 비교 시 **CR/LF를 자동 정규화**해서 `diff`/`cmp` 합니다.
* Python은 `run.sh`에서 `python -X utf8`로 실행해 **UTF-8 강제**.
* 템플릿들은 **stdin 파이프가 없으면 `input.txt`를 자동 사용**하므로
  `python foo.py`처럼 직접 실행해도 동작합니다.

---

## 🆘 트러블슈팅

* **페이지 요청 실패**: 네트워크/방화벽/인증서 이슈일 수 있습니다.
  `--debug`로 재시도 로그 확인, 임시로 `--insecure` 사용 가능.
* **solved.ac 429/오류**: 일시적 트래픽 제한일 수 있습니다. `--no-solvedac`으로 우회.
* **Windows C++ 빌드 실패**:

  * MSYS2 설치 및 `ucrt64` 구성 확인
  * `run.sh` 상단의 `UCRT_BASH`/`UCRT_ENV` 경로가 설치 위치와 일치하는지 확인
* **diff 없음**: Git Bash/MSYS2에 보통 포함됩니다. 없으면 `cmp -s`로 동등성만 체크합니다.

---

## 🗃️ 예시

```bash
# 현재 폴더명이 boj_17608_막대기 인 경우
python boj_init.py cpp --run
# => 17608 메타 파싱 → 파일 생성 → run.sh로 C++ 자동 채점
```

```bash
# 지정 경로에 문제 폴더 생성 후 세팅
export BOJ_DEST_BASE="$HOME/Desktop/TIS/Baekjoon"
python boj_init.py py --id 1006 --dest +week02/스택 --run
# => ~/Desktop/TIS/Baekjoon/week02/스택/1006.습격자_초라기/1006.습격자_초라기.py
#    tests, input.txt, run.sh 생성 후 파이썬 자동 채점
```

```bash
# 같은 문제를 다른 언어로 추가할 때
python boj_init.py java --id 1006 --dest +week02/스택         # 기존 tests/run.sh 유지
python boj_init.py cpp  --id 1006 --dest +week02/스택 -f      # -f로 run.sh 갱신 등 덮어쓰기
./run.sh "1006.습격자_초라기.java"                           # 특정 소스만 골라 실행
```
