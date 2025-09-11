import java.io.*;
import java.util.*;

public class chang_23968 {
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

        // 버블 정렬 수행
        int count = 0;
        outer: for (int end = N - 1; end > 0; end--) {
            for (int i = 0; i < end; i++) {
                // swap 조건 체크
                if (arr[i] > arr[i + 1]) {
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    count++;
                    if (count == K) {
                        System.out.println(arr[i] + " " + arr[i + 1]);
                        return;
                    }

                }
            }
        }
        System.out.println(-1);

    }
}
