import java.io.*;

public class donggeon_2231 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int M = 0;
        int input = Integer.parseInt(br.readLine());

        for (int i = 1; i <= input; i++) {
            int num = i;
            int sum = 0;
            while (num != 0) {
                sum += num % 10;
                num /= 10;
            }
            sum += i;

            if (input == sum) {
                M = i;
                break;
            }
        }
        System.out.println(M);
    }
}
