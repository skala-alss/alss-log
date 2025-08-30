import java.io.*;
public class chang_27433 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        long N = Integer.parseInt(br.readLine());

        long result = 1;
        for (int i = 1; i <= N; i++) {
            result = result *= i;
        }
        System.out.println(result);

    }
}
