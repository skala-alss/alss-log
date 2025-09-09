import java.io.*;
import java.util.StringTokenizer;

public class donggeon_2501 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        int cnt = 0;  // 특정 시점에서의 약수 개수

        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                cnt++;
            }
            if (cnt == k) {
                System.out.println(i);
                return;
            }
        }
        System.out.println(0);
    }
}