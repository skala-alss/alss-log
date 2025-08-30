import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class jiyun_27433 {
    static long factorial(long n){
        // 종료조건
        if(n==0 || n==1) return 1;

        return n * factorial(n-1);
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        long n = Integer.parseInt(br.readLine());

        System.out.println(factorial(n));
    }
}
