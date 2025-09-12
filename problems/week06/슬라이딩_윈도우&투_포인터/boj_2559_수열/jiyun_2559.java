package boj_2559_수열;

import java.util.*;
import java.io.*;

class jiyun_2559 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());

        int[] arr = new int[n];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }

        int sum = 0;
        for (int i = 0; i < k; i++) {
            sum += arr[i];
        }

        int maxSum = sum;

        for (int i = k; i < n; i++) {
            sum += arr[i] - arr[i - k];
            maxSum = Math.max(maxSum, sum);
        }
        System.out.println(maxSum);
    }
}