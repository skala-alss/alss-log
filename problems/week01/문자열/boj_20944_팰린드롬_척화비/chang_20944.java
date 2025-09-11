import java.io.*;
import java.util.*;
public class chang_20944 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        StringBuilder sb = new StringBuilder(N);
        for(int i = 0; i < N; i++) sb.append('a');

        System.out.println(sb.toString());
    }
}
