import java.io.*;
import java.util.*;

public class chang_24052 {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());

        int[] arr = new int[N];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        int count = 0;

        for (int i = 1; i < N; i++) {
            int key = arr[i];
            int j = i - 1;

            // shift: arr[j] > key 인 동안 arr[j+1]에 arr[j]를 저장
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                count++;
                if (count == K) {
                    for (int x : arr) System.out.print(x + " ");
                    System.out.println();
                    return;
                }
                j--;
            }

            // insert: key를 j+1 위치에 저장
            if (arr[j + 1] != key) {
                arr[j + 1] = key;
                count++;
                if (count == K) {
                    for (int x : arr) System.out.print(x + " ");
                    System.out.println();
                    return;
                }
            } else {
                arr[j + 1] = key;
            }
        }

        // K번째 저장이 없었음
        System.out.println(-1);
    }
}
