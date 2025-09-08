package boj_1940_주몽;

import java.util.*;
import java.io.*;

public class jiyun_1940 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int m = Integer.parseInt(br.readLine());

        int[] arr = new int[n];
        StringTokenizer st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }
        Arrays.sort(arr);

        int startPointer = 0;
        int endPointer = arr.length -1;
        int sum = 0;
        int count = 0;

        while(startPointer < endPointer){
            sum = arr[startPointer] + arr[endPointer];
            if(sum < m){
                startPointer++;
            } else if(sum > m){
                endPointer--;
            } else{
                startPointer++;
                endPointer--;
                count++;
            }
        }
        System.out.println(count);
    }
}