import java.io.*;

public class jiyun_1094 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int result = Integer.bitCount(n);

        System.out.println(result);
    }
}
