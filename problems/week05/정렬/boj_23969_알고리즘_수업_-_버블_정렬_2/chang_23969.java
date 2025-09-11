import java.io.*;
import java.util.*;

public class chang_23969 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken()); // 배열 크기
        int K = Integer.parseInt(st.nextToken()); // K번째 교환

        int[] arr = new int[N];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        int count = 0; // 교환 횟수 카운트
        for (int end = N - 1; end > 0; end--) {
            for (int i = 0; i < end; i++) {
                if (arr[i] > arr[i + 1]) {
                    // swap
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;

                    count++;
                    if (count == K) {
                        // 배열 전체 출력
                        StringBuilder sb = new StringBuilder();
                        for (int j = 0; j < N; j++) {
                            sb.append(arr[j]).append(" ");
                        }
                        System.out.println(sb.toString().trim());
                        return;
                    }
                }
            }
        }

        // K번째 교환이 발생하지 않으면 -1
        System.out.println(-1);
    }
}
