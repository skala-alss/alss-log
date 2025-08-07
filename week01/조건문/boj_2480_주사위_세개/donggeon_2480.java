import java.io.*;
import java.util.StringTokenizer;

public class donggeon_2480 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        int a = Integer.parseInt(st.nextToken());
        int b = Integer.parseInt(st.nextToken());
        int c = Integer.parseInt(st.nextToken());

        int prize = 0;
        if (a == b && b == c) {
            prize = 10000 + a * 1000;
        } else if (a == b || b == c || a == c) {
            if (a == b) {
                prize = 1000 + a * 100;
            } else if (b == c) {
                prize = 1000 + b * 100;
            } else {
                prize = 1000 + c * 100;
            }
        } else {
            int bigNum = a;
            if (bigNum < b) {
                bigNum = b;
            }
            if (bigNum < c) {
                bigNum = c;
            }
            prize = bigNum * 100;
        }

        System.out.println(prize);
    }
}
