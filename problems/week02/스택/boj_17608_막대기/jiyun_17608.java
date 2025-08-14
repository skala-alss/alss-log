import java.util.*;
import java.io.*;

public class jiyun_17608 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Deque<Integer> stack = new ArrayDeque<>();

        int n = Integer.parseInt(br.readLine());
        int[] arr = new int[n];

        for(int i=0;i<n;i++){
            int num = Integer.parseInt(br.readLine());
            arr[i] = num;
            stack.push(arr[i]);
        }

        int count=0;
        int max=0;
        while(!stack.isEmpty()){
            int cur = stack.pop();
            if(cur > max){
                count++;
                max=cur;
            }
        }

        System.out.println(count);
    }
}