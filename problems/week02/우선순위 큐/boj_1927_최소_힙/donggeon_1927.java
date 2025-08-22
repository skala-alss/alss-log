import java.io.*;
import java.util.Queue;
import java.util.PriorityQueue;

public class donggeon_1927 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = Integer.parseInt(br.readLine());

        Queue<Long> pq = new PriorityQueue<>();
        for (int i = 0; i < count; i++) {
            Long num = Long.parseLong(br.readLine());

            if (num > 0) {
                pq.add(num);
            } else if (num == 0) {
                if (!pq.isEmpty()) {
                    System.out.println(pq.poll());
                } else {
                    System.out.println(0);
                }
            }
        }
    }
}
