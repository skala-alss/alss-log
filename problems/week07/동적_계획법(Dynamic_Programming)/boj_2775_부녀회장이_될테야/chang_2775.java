import java.io.*;
import java.util.*;

public class chang_2775 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());

        // 최대 층수와 호수 범위 설정 (문제에서 보통 14까지)
        int MAX = 15;
        int[][] dp = new int[MAX][MAX];

        // 0층 초기화
        for (int i = 1; i < MAX; i++) {
            dp[0][i] = i;
        }

        // DP 채우기
        for (int k = 1; k < MAX; k++) {
            for (int n = 1; n < MAX; n++) {
                if (n == 1) {
                    dp[k][n] = 1;
                } else {
                    dp[k][n] = dp[k][n - 1] + dp[k - 1][n];
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int t = 0; t < T; t++) {
            int k = Integer.parseInt(br.readLine()); // 층
            int n = Integer.parseInt(br.readLine()); // 호
            sb.append(dp[k][n]).append("\n");
        }

        System.out.print(sb);
    }
}
