import java.io.*;
import java.util.StringTokenizer;
import java.util.ArrayDeque;

public class donggeon_1021 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        // 초기화
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        ArrayDeque<Integer> dq = new ArrayDeque<>();
        for (int i = 1; i <= n; i++) {
            dq.offer(i);
        }
        int cnt = 0;  // 이동 횟수

        // 연산 수행
        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= m; i++) {
            int target = Integer.parseInt(st.nextToken());
            int step = 0;
            for (int e : dq) {
                if (e == target) {
                    break;
                }
                step++;
            }

            if (step == 0) {
                dq.pollFirst();
                continue;
            }

            int right = step;  // 본인 원소 기준 오른쪽 몇 번째인지
            int left = dq.size() - step;  // 반대방향 = 현 dq 크기에서 step을 제외한 나머지

            // 큐 내 이동
            if (left >= right) {
                for (int j = 0; j < right; j++) {
                    dq.offerLast(dq.pollFirst());
                    cnt++;
                }
            } else {
                for (int j = 0; j < left; j++) {
                    dq.offerFirst(dq.pollLast());
                    cnt++;
                }
            }
            // 원소 뽑기
            dq.pollFirst();  
        }
        System.out.println(cnt);
    }
}
