import java.io.*;
import java.util.StringTokenizer;

public class donggeon_2559_2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());

        int[] arr = new int[n];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        // 슬라이딩 윈도우
        int sum = 0;
        for (int i = 0; i < k; i++) {
            sum += arr[i];
        }
        int sumMax = sum;

        for (int i = k; i < n; i++) {
            sum  = sum - arr[i - k] + arr[i];
            if (sum > sumMax) {
                sumMax = sum;
            }
        }

        System.out.println(sumMax);
    }
}
