import java.io.*;

public class jiyun_10870 {
    public static void main(String[] args) throws IOException{
       BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

       int n = Integer.parseInt(br.readLine());

       int[] arr = new int[n+1];
       arr[0] = 0;
       arr[1] = 1;

       for(int i=2;i<=n;i++){
           arr[i] = arr[i-2] + arr[i-1];
       }
        System.out.println(arr[n]);
    }
}
