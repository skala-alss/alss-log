package boj_21921_블로그;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_21921 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int days = Integer.parseInt(st.nextToken());
        int[] arr = new int[n];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }

        // 초기 세팅
        int sum=0;
        for(int i=0;i<days;i++){
            sum = sum + arr[i];
        }

        int maxSum = sum;
        int count =1;
        for(int i = days; i < n; i++) {
            sum = sum - arr[i - days] + arr[i];

            if(sum == maxSum){
                count++;
            }
            if(sum > maxSum){
                count = 1;
                maxSum = sum;
            }
        }
        if(maxSum ==0){
            System.out.println("SAD");
        } else {
            System.out.println(maxSum);
            System.out.println(count);
        }

    }
}
