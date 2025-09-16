package boj_1003_피보나치_함수;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class jiyun_1003 {
    public static void main(String[] args) throws IOException {
        // table로 관리하기
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int testCase = Integer.parseInt(br.readLine());

        // 0 <= testcase < = 40
        int[][] dp = new int[41][2];
        dp[0][0] = 1; dp[0][1] = 0;
        dp[1][0] = 0; dp[1][1] = 1;

        for(int i=2;i<=40;i++){
            dp[i][0] = dp[i-1][0] + dp[i-2][0];
            dp[i][1] = dp[i-1][1] + dp[i-2][1];
        }

        StringBuilder sb = new StringBuilder();
        for(int i=0;i<testCase;i++){
            int n = Integer.parseInt(br.readLine());
            sb.append(dp[n][0]).append(" ").append(dp[n][1]).append("\n");
        }
        System.out.println(sb);
    }
}
