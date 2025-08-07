import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class donggeon_10951 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String strLine;
        while ((strLine = br.readLine())  != null) {
            String[] input = strLine.split(" ");
            int A = Integer.parseInt(input[0]);
            int B = Integer.parseInt(input[1]);

            System.out.println(A + B);
        }
    }
}
