import java.io.*;
import java.util.ArrayDeque;
import java.util.StringTokenizer;

public class donggeon_28279 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        ArrayDeque<Integer> dq = new ArrayDeque<>();
        int count = Integer.parseInt(br.readLine());
        for (int i = 0; i < count; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int order = Integer.parseInt(st.nextToken());

            switch (order) {
                case 1:
                    dq.addFirst(Integer.parseInt(st.nextToken()));
                    break;
                case 2:
                    dq.addLast(Integer.parseInt(st.nextToken()));
                    break;
                case 3:
                    sb.append(!dq.isEmpty() ? dq.removeFirst() : -1).append("\n");
                    break;
                case 4:
                    sb.append(!dq.isEmpty() ? dq.removeLast() : -1).append("\n");
                    break;
                case 5:
                    sb.append(dq.size()).append("\n");
                    break;
                case 6:
                    sb.append(dq.isEmpty() ? 1 : 0).append("\n");
                    break;
                case 7:
                    sb.append(!dq.isEmpty() ? dq.peekFirst() : -1).append("\n");
                    break;
                case 8:
                    sb.append(!dq.isEmpty() ? dq.peekLast() : -1).append("\n");
                    break;
            }
        }

        System.out.print(sb.toString());
    }
}
