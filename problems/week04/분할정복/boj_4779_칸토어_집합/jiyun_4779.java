import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class jiyun_4779 {
    static StringBuilder sb;

    static void cantor(int start, int len) {
        if (len == 1) return;
        int third = len / 3;
        for (int i = start + third; i < start + 2 * third; i++) {
            sb.setCharAt(i, ' ');
        }
        cantor(start, third);
        cantor(start + 2 * third, third);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = br.readLine()) != null) {
            int n = Integer.parseInt(line);

            int total = (int) Math.pow(3,n);

            sb = new StringBuilder(total);
            for (int i = 0; i < total; i++) sb.append('-');

            cantor(0, total);
            System.out.println(sb.toString());
        }
    }
}

