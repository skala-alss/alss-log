import java.io.*;

public class donggeon_1065 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int input = Integer.parseInt(br.readLine());
        int cnt = 0;
        for (int i = 1; i <= input; i++) {
            cnt += chkHansu(i);
        }
        System.out.println(cnt);
    }

    public static int chkHansu(int n) {
        if (n < 100) {
            return 1;
        } else if (n == 1000) {
            return 0;
        }

        int digit_100 = n / 100;
        int digit_10 = (n / 10) % 10;
        int digit_1 = n % 10;
        if ((digit_100 - digit_10) == (digit_10 - digit_1)) {
            return 1;
        }
        return 0;
    }
}
