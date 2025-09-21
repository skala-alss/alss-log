import java.io.*;
import java.util.StringTokenizer;

public class donggeon_24060 {

    static int[] arr;
    static int[] tmp;
    static int cnt = 0;
    static int k;
    static int result = -1;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());
        arr = new int[n];
        tmp = new int[n];

        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        merge_sort(arr, 0, n - 1);
        System.out.println(result);
    }

    public static void merge_sort(int[] arr, int start, int end) {
        int mid = 0;
        if (start < end) {
            mid = (start + end) / 2;

            merge_sort(arr, start, mid);
            merge_sort(arr, mid + 1, end);
            merge(arr, start, mid, end);
        }
    }

    public static void merge(int[] arr, int start, int mid, int end) {
        int i = start;
        int j = mid + 1;
        int t = 0;
        while ((i <= mid) && (j <= end)) {
            if (arr[i] <= arr[j]) {
                tmp[t++] = arr[i++];
            } else {
                tmp[t++] = arr[j++];
            }
        }
        while (i <= mid) {  // 왼쪽 배열 부분이 남은 경우
            tmp[t++] = arr[i++];
        }
        while (j <= end) {  // 오른쪽 배열 부분이 남은 경우
            tmp[t++] = arr[j++];
        }

        // 결과를 다시 arr에 저장
        i = start;
        t = 0;
        while (i <= end) {
            arr[i] = tmp[t];
            cnt++;
            if (cnt == k) {
                result = arr[i];
                return;
            }
            i++;
            t++;
        }
    }
}
