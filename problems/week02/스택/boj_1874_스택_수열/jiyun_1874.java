import java.io.*;
import java.util.*;

public class jiyun_1874 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        Deque<Integer> stack = new ArrayDeque<>();

        int n = Integer.parseInt(br.readLine());
        int next = 1;

        for (int i = 0; i < n; i++) {
            int target = Integer.parseInt(br.readLine());

            while (next <= target) {
                stack.push(next++);
                sb.append("+\n");
            }

            if (!stack.isEmpty() && stack.peek() == target) {
                stack.pop();
                sb.append("-\n");
            } else {
                System.out.println("NO");
                return;
            }
        }
        System.out.print(sb.toString());
    }
}
