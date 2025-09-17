import java.io.*;
import java.util.Map;
import java.util.HashMap;

public class donggeon_17219 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Map<String, String> loginInfoMap = new HashMap<>();
        StringBuilder sb = new StringBuilder();

        String[] input = br.readLine().split(" ");
        int n = Integer.parseInt(input[0]);  // 저장된 사이트 주소 수
        int m = Integer.parseInt(input[1]);  // 비밀번호를 찾으려는 사이트 주소 수

        // 사이트 정보 입력 -> HashMap에 저장
        for (int i = 0; i < n; i++) {
            input = br.readLine().split(" ");
            loginInfoMap.put(input[0], input[1]);
        }

        // 사이트 key 기반 비밀번호 찾기
        for (int i = 0; i < m; i++) {
            String key = br.readLine();
            sb.append(loginInfoMap.get(key));
            if (i != m - 1) {
                sb.append('\n');
            }
        }
        System.out.println(sb);
    }
}
