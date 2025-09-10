import java.io.*;
import java.util.StringTokenizer;

public class donggeon_24051 {

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

        // 삽입 정렬 및 출력
        insertion_sort(arr);
    }

    public static void insertion_sort(int[] arr) {
        int cnt = 0;
        for (int i = 1; i < arr.length; i++) {
            int item = arr[i];
            int loc = i - 1;

            while ((loc >= 0) && (arr[loc] > item)) {
                arr[loc + 1] = arr[loc];
                cnt++;
                if (cnt == k) {
                    System.out.println(arr[loc]);
                    return;
                }

                loc--;
            }
            if (loc + 1 != i) {
                arr[loc + 1] = item;
                cnt++;
                if (cnt == k) {
                    System.out.println(item);
                    return;
                }
            }
        }
        System.out.println(-1);
    }
}
