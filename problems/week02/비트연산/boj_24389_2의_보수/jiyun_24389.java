import java.io.*;

public class jiyun_24389 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());
        // bin_n을 보수로
        int com_n = ~n+1;

        int result = n ^ com_n;
        int cnt = 0;

        for(char ch : Integer.toBinaryString(result).toCharArray()){
            if(ch == '1') cnt++;
        }
        System.out.println(cnt);
    }
}
