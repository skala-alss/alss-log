import java.io.*;
import java.util.StringTokenizer;

public class donggeon_15649 {
    static int N, M;
    static int[] arr;
    static boolean[] visited;
    static StringBuilder sb = new StringBuilder();

    static void backTracking(int depth) {
        if (depth == M) {
            for (int val : arr) {
                sb.append(val).append(' ');
            }
            sb.append('\n');
            return;
        }

        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {  //해당 노드가 방문되지 않았다면
                visited[i] = true;  //해당 노드를 방문상태로 변경
                arr[depth] = i;
                backTracking(depth + 1);  //다음 자식 노드 방문

                //자식 노드 방문이 끝나고 돌아오면 방문노드를 방문하지 않은 상태로 변경
                visited[i] = false;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        arr = new int[M];
        visited = new boolean[N + 1];  //인덱스와 숫자 사이 불일치 혼란 방지

        backTracking(0);
        System.out.print(sb.toString());
    }
}
