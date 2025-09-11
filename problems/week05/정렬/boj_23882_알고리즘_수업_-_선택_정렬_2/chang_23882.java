import java.io.*;
import java.util.*;

public class chang_23882 {
    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken()); // 배열 크기
        int K = Integer.parseInt(st.nextToken()); // K번째 swap
        int[] arr = new int[N];

        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        int swapCount = 0;

        // 선택 정렬 (끝에서 앞으로)
        for (int last = N - 1; last > 0; last--) {
            int maxIdx = last;
            // 0 ~ last 까지 중 최댓값 찾기
            for (int j = 0; j < last; j++) {
                if (arr[j] > arr[maxIdx]) {
                    maxIdx = j;
                }
            }

            // swap이 필요한 경우에만
            if (maxIdx != last) {
                swapCount++;
                swap(arr, last, maxIdx);

                // K번째 swap이면 배열 전체 출력
                if (swapCount == K) {
                    StringBuilder sb = new StringBuilder();
                    for (int num : arr) sb.append(num).append(" ");
                    System.out.println(sb.toString().trim());
                    return;
                }
            }
        }

        // 끝까지 swapCount < K라면
        System.out.println(-1);
    }
}
