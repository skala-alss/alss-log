import java.io.*;
import java.util.*;

public class chang_24051 {
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

            // shift: arr[j] > key인 동안 arr[j+1]에 arr[j]를 '저장'
            while (j >= 0 && arr[j] > key) {
                // 실제 값이 바뀌는 저장만 카운트
                if (arr[j + 1] != arr[j]) {
                    arr[j + 1] = arr[j];
                    count++;
                    if (count == K) {
                        System.out.println(arr[j]); // 방금 저장된 값
                        return;
                    }
                } else {
                    // 값이 같으면 카운트하지 않지만, 대입은 수행하여 상태 유지
                    arr[j + 1] = arr[j];
                }
                j--;
            }

            // insert: key를 j+1 위치에 '저장'
            if (arr[j + 1] != key) {
                arr[j + 1] = key;
                count++;
                if (count == K) {
                    System.out.println(key); // 방금 저장된 값
                    return;
                }
            } else {
                // 값이 같으면 카운트하지 않음
                arr[j + 1] = key;
            }
        }

        // K번째 저장이 없었음
        System.out.println(-1);
    }
}
