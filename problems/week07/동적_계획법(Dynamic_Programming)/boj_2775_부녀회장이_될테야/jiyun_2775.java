package boj_2775_부녀회장이_될테야;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class jiyun_2775 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int testCase = Integer.parseInt(br.readLine());

        // 1 ≤ k, n ≤ 14
        int[][] apt = new int[15][15];
        for (int i = 1; i < 15; i++) {
            apt[0][i] = i;
        }
        for(int k=1;k<15;k++){
            for(int n=1;n<15;n++){
                apt[k][n] = apt[k][n - 1] + apt[k - 1][n];
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < testCase; i++) {
            int k = Integer.parseInt(br.readLine());
            int n = Integer.parseInt(br.readLine());
            sb.append(apt[k][n]).append("\n");
        }
        System.out.print(sb);
    }
}
