import java.io.*;

public class jiyun_2231 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int result = 0;
        // n = (100*a + 10*b + 1*c) + a + b + c
        for(int i=0;i<n+1;i++){

            int temp=i;
            int sum=0;

            while(temp != 0){
                sum += temp % 10;
                temp /= 10;
            }

            if(i + sum == n){
                result = i;
                break;
            }
        }
        System.out.println(result);
    }
}

