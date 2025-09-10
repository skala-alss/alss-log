import java.io.*;
import java.util.StringTokenizer;

public class donggeon_23968 {

    static int k;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());

        int[] arr = new int[n];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        // 버블 정렬 및 출력
        bubble_sort(arr);
    }

    public static void bubble_sort(int[] arr) {
        int cnt = 0;
        for (int i = arr.length - 1; i >= 1; i--) {
            for (int j = 0; j < arr.length - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    cnt++;
                }

                if (cnt == k) {
                    System.out.println(arr[j] + " " + arr[j + 1]);
                    return;
                }
            }
        }
        System.out.println(-1);
    }
}
