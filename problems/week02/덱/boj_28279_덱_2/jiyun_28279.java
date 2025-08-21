import java.io.*;
import java.util.*;

public class jiyun_28279 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        Deque<Integer> deque = new ArrayDeque<>();
        int n = Integer.parseInt(br.readLine());

        for(int i=0;i<n;i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int command = Integer.parseInt(st.nextToken());
            switch (command) {
                case 1:
                    deque.offerFirst(Integer.parseInt(st.nextToken()));
                    break;
                case 2:
                    deque.offerLast(Integer.parseInt(st.nextToken()));
                    break;
                case 3:
                    sb.append(deque.isEmpty() ? "-1" : deque.pollFirst()).append("\n");
                    break;
                case 4:
                    sb.append(deque.isEmpty() ? "-1" : deque.pollLast()).append("\n");
                    break;
                case 5:
                    sb.append(deque.size()).append("\n");
                    break;
                case 6:
                    sb.append(deque.isEmpty() ? "1" : "0").append("\n");
                    break;
                case 7:
                    sb.append(deque.isEmpty() ? "-1" : deque.peekFirst()).append("\n");
                    break;
                case 8:
                    sb.append(deque.isEmpty() ? "-1" : deque.peekLast()).append("\n");
                    break;
            }
        }
        System.out.println(sb.toString());
    }
}