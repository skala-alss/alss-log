import java.io.*;
import java.util.PriorityQueue;
import java.util.Collections;  //최대 힙 구현을 위해 필요

public class donggeon_11279 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        int count = Integer.parseInt(br.readLine());
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());  //최대 힙
        for (int i = 0; i < count; i++) {
            int num = Integer.parseInt(br.readLine());
            if (num == 0) {  //입력이 0일 때만 별도 처리
                if (pq.isEmpty()) {
                    sb.append(0).append("\n");
                } else {
                    sb.append(pq.poll()).append("\n");
                }
            } else {
                pq.offer(num);
            }
        }

        System.out.print(sb.toString());
    }
}
