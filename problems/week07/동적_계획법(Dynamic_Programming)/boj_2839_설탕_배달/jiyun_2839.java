package boj_2839_설탕_배달;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class jiyun_2839 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int input = Integer.parseInt(br.readLine());

        // 5x + 3y = input
        int[] dp = new int[input+1];
        Arrays.fill(dp,-1);

        dp[0] = 0;
        for (int i=1;i<input +1;i++){
            if( i >= 5 && dp[i-5] != -1){
                dp[i] = (dp[i] == -1) ? dp[i-5] + 1 : Math.min(dp[i], dp[i-5] + 1);
            }
            if( i >= 3 && dp[i-3] != -1){
                dp[i] = (dp[i] == -1) ? dp[i-3] + 1 : Math.min(dp[i], dp[i-3] + 1);
            }
        }
        System.out.println(dp[input]);
    }
}
