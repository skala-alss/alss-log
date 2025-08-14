import java.util.*;
import java.io.*;

public class jiyun_12605 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());
        Deque<String> stack = new ArrayDeque<>();

        for(int i=0;i<n;i++){
            String input = br.readLine();
            String[] arr = input.split(" ");
            for(int j=0;j<arr.length;j++){
                stack.push(arr[j]);
            }

            System.out.printf("Case #%d: ",(i+1));
            while(!stack.isEmpty()){
                System.out.print(stack.pop());
                System.out.print(" ");
                if(stack.isEmpty()){
                    System.out.println();
                }
            }
        }
    }
}