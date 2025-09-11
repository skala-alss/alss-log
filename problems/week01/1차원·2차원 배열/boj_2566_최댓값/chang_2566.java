import java.io.*;
import java.util.*;
public class chang_2566 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));



        int maxValue = -1;
        int row=1, col=1;

        for (int i = 1; i <= 9; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int j = 1; j <= 9; j++) {
                int val = Integer.parseInt(st.nextToken());
                if (val > maxValue) {
                    maxValue = val;
                    row = i;
                    col = j;
                }
            }
        }
        System.out.println(maxValue);
        System.out.println(row + " " + col);
    }
}
