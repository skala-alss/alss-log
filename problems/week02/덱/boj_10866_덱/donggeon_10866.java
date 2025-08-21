import java.io.*;
import java.util.Deque;
import java.util.ArrayDeque;
import java.util.StringTokenizer;

public class donggeon_10866 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Deque<String> dq = new ArrayDeque<String>();

        int count = Integer.parseInt(br.readLine());

        for (int i = 0; i < count; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            String order = st.nextToken();

            switch(order) {
                case "push_front":
                    dq.addFirst(st.nextToken());
                    break;
                case "push_back":
                    dq.addLast(st.nextToken());
                    break;
                case "pop_front":
                    if (!dq.isEmpty()) { System.out.println(dq.removeFirst()); }
                    else { System.out.println(-1); }
                    break;
                case "pop_back":
                    if (!dq.isEmpty()) { System.out.println(dq.removeLast()); }
                    else { System.out.println(-1); }
                    break;
                case "size":
                    System.out.println(dq.size());
                    break;
                case "empty":
                    if (dq.isEmpty()) { System.out.println(1); }
                    else { System.out.println(0); }
                    break;
                case "front":
                    if (!dq.isEmpty()) { System.out.println(dq.peekFirst()); }
                    else { System.out.println(-1); }
                    break;
                case "back":
                    if (!dq.isEmpty()) { System.out.println(dq.peekLast()); }
                    else { System.out.println(-1); }
                    break;
            }
        }
    }
}
