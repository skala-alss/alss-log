import java.io.*;
import java.util.*;
public class chang_2309 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int[] h = new int[9];
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            h[i] = Integer.parseInt(br.readLine());
            sum += h[i];
        }

        int x = -1, y= -1;
        outer:
        for (int i = 0; i < 8; i++){
            for (int j = i+1; j < 9; j++){
                if (sum - h[i] - h[j] == 100){
                    x = i; y = j;
                    break outer;
                }
            }
        }

        int[] ans = new int[7];
        int idx = 0;
        for (int i = 0; i < 9; i++){
            if (i== x || i == y) continue;
            ans[idx++] = h[i];
        }

        Arrays.sort(ans);
        StringBuilder sb = new StringBuilder();
        for (int v : ans) sb.append(v).append('\n');
        System.out.println(sb.toString());
    }
}
