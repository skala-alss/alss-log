import java.io.*;

public class donggeon_10952 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int A = 0;
        int B = 0;

        while (true) {
            String[] input = br.readLine().split(" ");
            A = Integer.parseInt(input[0]);
            B = Integer.parseInt(input[1]);
            if (A == 0 && B == 0) {
                break;
            }
            System.out.println(A + B);
        }
    }
}
