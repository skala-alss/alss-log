import java.io.*;
import java.util.StringTokenizer;

public class donggeon_15652 {
    static int N, M;
    static StringBuilder sb = new StringBuilder();
    static int[] arr;

    public static void backTracking(int depth) {
        if (depth == M) {
            for (int val : arr) {
                sb.append(val).append(' ');
            }
            sb.append('\n');
            return;
        }

        for (int i = 1; i <= N; i++) {
            if ((depth >= 1) && (arr[depth - 1] > i)) {
                continue;
            } else {
                arr[depth] = i;
                backTracking(depth + 1);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        arr = new int[M];

        backTracking(0);

        System.out.println(sb);
    }
}
