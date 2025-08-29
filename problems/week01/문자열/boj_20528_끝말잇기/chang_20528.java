import java.util.*;
import java.io.*;
public class chang_20528 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());


        boolean ok = true;
        String line = br.readLine();
        StringTokenizer st = new StringTokenizer(line);
        String[] words = new String[N];
        for (int i = 0; i < N; i++) {
            words[i] = st.nextToken();
        }


        char target = words[0].charAt(0);
        for (int i = 1; i < N; i++) {
            if (words[i].charAt(0) != target) {
                ok = false;
                break;
            }
        }


        if (ok) System.out.println(1);
        else System.out.println(0);
    }
}
