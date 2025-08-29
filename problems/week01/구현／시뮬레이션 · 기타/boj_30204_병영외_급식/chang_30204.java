import java.io.*;
import java.util.*;
public class chang_30204 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int X = Integer.parseInt(st.nextToken());


        int sum = 0;
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            if (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            sum += Integer.parseInt(st.nextToken());
        }

        if (sum % X == 0){
            System.out.println(1);
        }else {
            System.out.println(0);
        }
    }
}
