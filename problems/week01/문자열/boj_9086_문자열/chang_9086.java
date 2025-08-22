import java.io.*;
import java.util.StringTokenizer;

public class chang_9086 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int T = Integer.parseInt(br.readLine().trim());
        for (int i = 0; i < T; i++){
            String s = br.readLine().trim();
            char first = s.charAt(0);
            char last = s.charAt(s.length()-1);
            out.append(first).append(last).append('\n');
        }

        System.out.println(out.toString());
    }
}
