import java.io.*;

public class donggeon_2420 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        long N = Long.parseLong(input[0]);
        long M = Long.parseLong(input[1]);
        long diffAbs = Math.abs(N - M);
        System.out.println(diffAbs);
    }
}
