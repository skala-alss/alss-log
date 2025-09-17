import java.io.*;
import java.util.Comparator;
import java.util.PriorityQueue;

public class donggeon_11286 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        int n = Integer.parseInt(br.readLine());
        // 커스텀 Comparator 정의
        PriorityQueue<Integer> pq = new PriorityQueue<>(new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b) {
                int A = Math.abs(a);
                int B = Math.abs(b);
                if (A == B) {
                    return a - b;  // 반환값 음수 -> 앞의 수가 더 작으니 그대로 a가 앞에 위치
                }
                return A - B;
            }
        });

        for (int i = 0; i < n; i++) {
            int num = Integer.parseInt(br.readLine());
            if (num != 0) {
                pq.offer(num);
            } else {
                sb.append(pq.isEmpty() ? 0 : pq.poll()).append('\n');
            }
        }

        System.out.println(sb);
    }
}
