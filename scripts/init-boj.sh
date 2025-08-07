#!/usr/bin/env bash
# ============================================================================
# BOJ 문제 폴더 자동 세팅 스크립트
#   사용:  ./init_boj.sh <cpp|py|java> [--run]
#   전제:  현재 디렉터리명이 'boj_<번호>_<제목>' 형식
# ----------------------------------------------------------------------------
# 수정 포인트 (팀원별):  ① USERNAME
# ============================================================================
set -euo pipefail
export LANG=C.UTF-8
export LC_ALL=C.UTF-8

USERNAME="jinyeop"        # ← 여기에 본인 깃허브/닉네임 기입

# ─────────────────────────────────────── 0. 인자 처리
[[ $# -lt 1 ]] && { echo "사용법: $0 <cpp|py|java> [--run]"; exit 1; }
lang="$1"; shift || true

case "$lang" in
  cpp|c++|cpp17) lang="cpp" ;;
  py|python)     lang="py"  ;;
  java)                  ;;
  *) echo "❗ 지원하지 않는 언어: $lang"; exit 1 ;;
esac

# ─────────────────────────────────────── 1. 폴더명 → 문제번호 파싱
folder="$(basename "$PWD")"
if [[ ! $folder =~ ^[Bb][Oo][Jj]_([0-9]+)_.*$ ]]; then
  echo "❗ 폴더명이 'boj_2566_제목' 형식이어야 합니다."; exit 1
fi
pid="${BASH_REMATCH[1]}"

# ─────────────────────────────────────── 2. BOJ HTML 가져오기
user_agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64)"
referer="https://www.acmicpc.net/"
accept="text/html,application/xhtml+xml"
accept_lang="en-US,en;q=0.9"

html=$(curl -sL \
  -A "$user_agent" \
  -H "Referer: $referer" \
  -H "Accept: $accept" \
  -H "Accept-Language: $accept_lang" \
  "https://www.acmicpc.net/problem/$pid")

# ─────────────────────────────────────── 3. 제목 추출
title=$(echo "$html" | perl -ne '
  if (m{<span id="problem_title">(.*?)</span>}s) {
    $t = $1;
    $t =~ s/^\s+|\s+$//g;
    print $t;
  }
')

# fallback: <title> 태그에서 추출
if [[ -z $title ]]; then
  title=$(echo "$html" | perl -ne '
    if (m{<title>(.*?)</title>}s) {
      $t = $1;
      $t =~ s/^[^:]*:\s*//;
      $t =~ s/\s*-\s*BOJ$//;
      print $t;
    }
  ')
fi

[[ -z $title ]] && { echo "❗ 제목을 추출하지 못했습니다." >&2; exit 1; }
echo "▶ 제목: $title"

# ─────────────────────────────────────── 4. 예제 입력 파싱
sample=$(echo "$html" | perl -0777 -ne '
  while(m{<pre[^>]*id="sample-input[^>]*>(.*?)</pre>}sig){
    $t=$1;$t=~s/<br[^>]*>/\n/gi;$t=~s/&nbsp;/ /g;$t=~s/&#13;//g;$t=~s/<[^>]*>//g;
    $t=~s/^\s+|\s+$//g;print $t,"\n\n";
  }')
[[ -z $sample ]] && echo "⚠️  예제 입력 미발견 → 빈 input.txt 생성"

# ─────────────────────────────────────── 5. 파일명 설정
prefix="boj_${pid}_${USERNAME}"
case "$lang" in
  cpp)  src="${prefix}.cpp"  ;;
  py)   src="${prefix}.py"   ;;
  java) src="${prefix}.java" ;;
esac
build="build.sh"

[[ -e $src ]] && { echo "❗ '$src' 이미 존재, 중단"; exit 1; }

# ─────────────────────────────────────── 6. input.txt 생성
printf "%s" "${sample:-}" > input.txt

# ─────────────────────────────────────── 7. 언어별 스니펫 & build.sh
if [[ $lang == "cpp" ]]; then
cat <<EOF > "$src"
// ${title} (${pid})
// https://www.acmicpc.net/problem/${pid}

#include <iostream>
// #include <windows.h>

using namespace std;

int main()
{
    // SetConsoleOutputCP(CP_UTF8);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    std::cout << "N: " << N << ", M: " << M << "\n";

    return 0;
}
EOF

cat <<'EOF' > "$build"
#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"

echo "🔍 현재 디렉토리의 C++ 파일 목록:"
select file in *.cpp; do
  if [[ -n "$file" ]]; then break; fi
done

exe="main.exe"

echo "⚙️ 컴파일: $file → $exe"
g++ "$file" -std=c++14 -O2 -o "$exe"

echo "✅ 빌드 완료, 실행:"
if [[ -f input.txt ]]; then
  ./"$exe" < input.txt
else
  ./"$exe"
fi
EOF
chmod +x "$build"

mkdir -p .vscode

cat << 'EOF' > .vscode/c_cpp_properties.json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.22621.0",
            "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
            "cStandard": "c99",
            "cppStandard": "c++14",
            "intelliSenseMode": "windows-gcc-x64",
            "configurationProvider": "ms-vscode.cpptools"
        }
    ],
    "version": 4
}
EOF

elif [[ $lang == "py" ]]; then
cat <<EOF > "$src"
# ${title} (${pid})
# https://www.acmicpc.net/problem/${pid}

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    N, M = map(int, sys.stdin.readline().split())

    print(f"N: {N} M: {M}")

if __name__ == "__main__":
    main()

EOF

else   # java
classname="boj_${pid}_${USERNAME}"
cat <<EOF > "$src"
/**
 * ${pid} – ${title}
 * https://www.acmicpc.net/problem/${pid}
 */

import java.io.*;
import java.util.*;


// public class Main {
public class ${classname} {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        System.out.println("N: " + N + " M: " + M);
    }
}

EOF

fi

echo -n "✅ 생성 완료 → $src  input.txt"
[[ $lang == "cpp" ]] && echo "  $build" || echo ""

# ─────────────────────────────────────── 8. VS Code 열기
if command -v code.cmd &>/dev/null; then
  code.cmd .
elif command -v code &>/dev/null; then
  code .
else
  echo "⚠️ VSCode 명령(code) 를 찾을 수 없습니다."
fi
