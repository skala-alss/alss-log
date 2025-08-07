import java.io.*;
import java.util.StringTokenizer;

public class donggeon_2475 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");

        int sum = 0;
        int verifyNum;
        for (int i = 0; i < 5; i++) {
            int num = Integer.parseInt(st.nextToken());
            sum +=  num * num;
        }
        verifyNum = sum % 10;
        System.out.println(verifyNum);
    }
}
