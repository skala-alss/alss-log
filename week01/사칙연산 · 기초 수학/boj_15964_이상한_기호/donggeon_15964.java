import java.io.*;
import java.util.StringTokenizer;

public class donggeon_15964 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");

        long A = Long.parseLong(st.nextToken());
        long B = Long.parseLong(st.nextToken());

        br.close();
        System.out.println((A + B) * (A - B));
    }
}
