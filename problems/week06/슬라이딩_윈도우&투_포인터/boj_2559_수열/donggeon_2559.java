import java.io.*;
import java.util.StringTokenizer;

public class donggeon_2559 {
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

        int sumMax = Integer.MIN_VALUE;  // 연속적인 k일의 온도 합이 최대가 되는 값
        for (int i = 0; i < n - k + 1; i++) {
            int sum = 0;  // 한 번 k일 동안의 온도 합
            for (int j = i; j < i + k; j++) {
                sum += arr[j];
            }

            if (sum > sumMax) {
                sumMax = sum;
            }
        }
        System.out.println(sumMax);
    }
}
