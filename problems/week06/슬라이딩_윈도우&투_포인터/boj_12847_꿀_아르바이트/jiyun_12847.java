package boj_12847_꿀_아르바이트;

import java.util.*;
import java.io.*;

class jiyun_12847 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int[] arr = new int[n];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }

        long sum =0;
        for(int i = 0; i < m; i++) {
            sum += arr[i];
        }

        long maxSum = sum;

        for(int i = m; i < n; i++) {
            sum = sum - arr[i - m] + arr[i];
            maxSum = Math.max(maxSum, sum);
        }
        System.out.println(maxSum);
    }
}