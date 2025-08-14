import java.io.InputStreamReader;
import java.io.IOException;
import java.io.BufferedReader;

public class donggeon_10872 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int input = Integer.parseInt(br.readLine());

        int factResult = factorial(input);
        System.out.println(factResult);
    }

    public static int factorial(int num) {
        if (num <= 1) {
            return 1;
        }
        return num * factorial(num - 1);
    }
}
