import java.io.*;
import java.util.StringTokenizer;

public class donggeon_23881 {

    static int n, k;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());

        // 배열 값 할당
        st = new StringTokenizer(br.readLine());
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        // 선택 정렬 진행
        selection_sort(arr);
    }

    public static void selection_sort(int[] arr) {
        int cnt = 0;  // 교환 횟수
        for (int i = arr.length - 1; i >= 0; i--) {
            int idx = i;  // 현재 위치를 idx로 초기화
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] > arr[idx]) {
                    idx = j;  // 가장 큰 곳의 index를 idx에 할당
                }
            }
            if (idx != i) {  // swap
                int temp = arr[i];
                arr[i] = arr[idx];
                arr[idx] = temp;
                cnt++;
            }
            if (cnt == k) {
                System.out.println(arr[idx] + " " + arr[i]);
                return;
            }
        }
        System.out.println(-1);
    }
}
