# 📚 공식 문서와 언어별 개발 문화

알고리즘 문제 풀이와 코드 리뷰 스터디를 운영함에 있어 **공식 문서의 습관적 활용**과 **언어별 코드 작성 문화에 대한 이해**는 매우 중요합니다.
이는 문제 해결 능력뿐 아니라 **실무에서의 협업과 유지보수 역량**까지 길러주는 좋은 습관입니다.

## 🔗 공식 문서(레퍼런스)의 중요성

* **정확한 문법**과 **표준 API 사용법**을 확인할 수 있는 1차 정보원
* 특정 함수, 키워드, 클래스가 어떤 버전부터 지원되는지 추적 가능
* 실수나 오해를 방지하고, 최신 동향에 맞춘 학습 가능

| 언어         | 공식 문서                                                                         |
| ---------- | ----------------------------------------------------------------------------- |
| **C++**    | [cppreference](https://en.cppreference.com/) / [ISO C++](https://isocpp.org/) |
| **Java**   | [Oracle Java SE Documentation](https://docs.oracle.com/en/java/javase/)       |
| **Python** | [Python 공식 문서](https://docs.python.org/ko/3/) / [Python 자습서](https://docs.python.org/ko/3.13/tutorial/index.html)                                    |

> **Tip**: 코드 작성 중 헷갈리는 문법이나 기능은 공식 문서를 먼저 확인하세요.
> ChatGPT나 블로그도 좋지만, 신뢰도는 공식 문서가 가장 높습니다.

---

## 🧑‍💻 언어별 코드 스타일 및 도구

### 🔹 C++ (GCC / Clang)

* **컨벤션**: Google C++ Style Guide 참고 권장
* **기본 스타일**:

  * Snake\_case 또는 CamelCase 변수명
  * Header 분리, 함수별 주석 등 명확한 구조
* **포매터**: [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html)

  * `.clang-format` 파일로 팀 컨벤션 통일 가능
* **린터**: `clang-tidy`, `cppcheck`

> **추천 확장** (VSCode):
>
> * C/C++ Extension Pack
> * Clangd / Clang-Format

---

### 🔸 Java (OpenJDK 11+)

* **컨벤션**: [Google Java Style Guide](https://google.github.io/styleguide/javaguide.html)
* **기본 스타일**:

  * `PascalCase` 클래스명, `CamelCase` 변수/메서드명
  * 명확한 타입 명시, 주석 문서화 (`/** */`)
* **포매터**: `google-java-format`, IntelliJ 자동 포매터
* **린터**: `Checkstyle`, `SpotBugs`

> **추천 확장** (VSCode):
>
> * Extension Pack for Java
> * Java Language Support by Red Hat
> * Checkstyle for Java

---

### 🟦 Python (3.10+)

* **컨벤션**: [PEP 8](https://peps.python.org/pep-0008/) / [PEP 8 Korean](https://zerosheepmoo.github.io/pep8-in-korean/)
* **기본 스타일**:

  * Snake\_case 함수/변수, 클래스는 `CamelCase`
  * Type Hint 적극 사용 (예: `def func(x: int) -> str:`)
* **포매터**: `black`, `autopep8`
* **린터**: `flake8`, `pylint`, `mypy` (정적 타입 검사)

> **추천 확장** (VSCode):
>
> * Python Extension Pack
> * Pylance (IntelliSense 향상)
> * Black Formatter

---

## ✅ 스터디 권장 사항 요약

* 문제 풀이 시 **공식 문서**를 자주 참고하고, **정확하고 신뢰도 높은 정보**를 기반으로 학습하세요.
* 팀 프로젝트처럼 코드 스타일을 통일하기보다는, **각 언어의 표준 스타일 가이드를 따르는 연습**을 권장합니다.
  포매터와 린트 도구를 함께 사용하면 **코드를 더 깔끔하고 일관성 있게 유지**할 수 있으며, 리뷰나 복습에도 도움이 됩니다.
* 기본 템플릿/스니펫은 제공된 **자동 생성 스크립트**를 활용하고, **의미 있는 변수명과 주석**으로 자신의 코드를 설명해보는 습관을 길러보세요.
