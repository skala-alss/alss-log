import java.io.*;
import java.util.*;

public class jiyun_10866 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Deque<Integer> dq = new ArrayDeque<>();
        int n = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            String cmd = st.nextToken();

            switch (cmd) {
                case "push_front":
                    dq.addFirst(Integer.parseInt(st.nextToken()));
                    break;
                case "push_back":
                    dq.addLast(Integer.parseInt(st.nextToken()));
                    break;
                case "pop_front":
                    sb.append(dq.isEmpty() ? -1 : dq.removeFirst()).append('\n');
                    break;
                case "pop_back":
                    sb.append(dq.isEmpty() ? -1 : dq.removeLast()).append('\n');
                    break;
                case "size":
                    sb.append(dq.size()).append('\n');
                    break;
                case "empty":
                    sb.append(dq.isEmpty() ? 1 : 0).append('\n');
                    break;
                case "front":
                    sb.append(dq.isEmpty() ? -1 : dq.getFirst()).append('\n');
                    break;
                case "back":
                    sb.append(dq.isEmpty() ? -1 : dq.getLast()).append('\n');
                    break;
            }
        }
        System.out.print(sb.toString());
    }
}
