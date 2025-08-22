import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;  // 스택을 쓰려면 이걸 import 해야 함

public class chang_17608 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());

        // 스택 준비
        Stack<Integer> stack = new Stack<>();

        // 입력받은 막대 높이를 스택에 넣기
        for (int i = 0; i < n; i++) {
            int h = Integer.parseInt(br.readLine().trim());
            stack.push(h);  // push = 스택에 넣기
        }

        int count = 0;   // 보이는 막대 수
        int maxH = 0;    // 지금까지 본 가장 높은 막대

        // 스택에서 하나씩 꺼내며 확인 (오른쪽 → 왼쪽 순서)
        while (!stack.isEmpty()) {
            int h = stack.pop();  // pop = 스택에서 빼기
            if (h > maxH) {       // 지금까지 최고 높이보다 크면 보임
                count++;
                maxH = h;         // 최고 높이 갱신
            }
        }

        System.out.println(count);
    }
}
