import java.io.*;
import java.util.StringTokenizer;

public class donggeon_12847 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        int[] payArr = new int[n];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            payArr[i] = Integer.parseInt(st.nextToken());
        }

        long sum = 0;
        for (int i = 0; i < m; i++) {
            sum += payArr[i];
        }
        long maxRevenue = sum;

        for (int i = m; i < n; i++) {
            sum = sum - payArr[i - m] + payArr[i];
            if (sum > maxRevenue) {
                maxRevenue = sum;
            }
        }

        System.out.println(maxRevenue);
    }
}
