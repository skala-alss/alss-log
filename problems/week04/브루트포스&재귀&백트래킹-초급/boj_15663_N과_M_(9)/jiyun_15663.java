import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.Arrays;

class jiyun_15663 {
    static int n,m;
    static int[] input;
    static int[] result;
    static boolean flag[];
    static StringBuilder sb = new StringBuilder();

    static void Backtracking(int depth){
        if(depth==m){
            for(int i=0; i<m; i++) sb.append(result[i]).append(' ');
            sb.append('\n');
            return;
        }
        for(int i=0;i<n;i++){
            if (flag[i]) continue;
            if (i > 0 && input[i] == input[i - 1] && !flag[i - 1]) continue;
            flag[i] = true;
            result[depth] = input[i];
            Backtracking(depth + 1);
            flag[i] = false;
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        flag = new boolean[n];
        input = new int[n];
        result = new int[m];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            input[i] = Integer.parseInt(st.nextToken());
        }
        Arrays.sort(input);
        n=input.length;

        Backtracking(0);
        System.out.println(sb);
    }
}