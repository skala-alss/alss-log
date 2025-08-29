import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
public class chang_15649 {
        static int N, M;
        static int[] path;
        static boolean[] visited;
        static StringBuilder sb = new StringBuilder();

        static void dfs(int depth){
            if (depth == M){
                for(int i = 0; i < M; i++){
                    if (i > 0) sb.append(' ');
                    sb.append(path[i]);
                }
                sb.append('\n');
                return;
            }

            for (int i = 1; i <=N; i++){
                if (!visited[i]) {
                    visited[i] = true;
                    path[depth]= i;
                    dfs(depth + 1);
                    visited[i] = false;
                }
            }

        }

public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine().trim());
     N = Integer.parseInt(st.nextToken());
     M = Integer.parseInt(st.nextToken());

    path = new int[M];
    visited = new boolean[N+1];

    dfs(0);
    System.out.println(sb);
  }
}