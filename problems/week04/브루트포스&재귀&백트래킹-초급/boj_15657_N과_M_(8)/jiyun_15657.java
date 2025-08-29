import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class jiyun_15657 {
    static int n,m;
    static int[] arr;
    static int[] result;
    static StringBuilder sb = new StringBuilder();

    static void Backtracking(int depth, int start){
        if(depth==m){
            for(int i=0; i<m; i++) sb.append(result[i]).append(' ');
            sb.append('\n');
            return;
        }
        for(int i=start;i<n;i++){
            result[depth] = arr[i];
            Backtracking(depth+1, i);
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        arr= new int[n];
        result = new int[m];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            int input = Integer.parseInt(st.nextToken());
            arr[i]=input;
        }
        Arrays.sort(arr);

        Backtracking(0, 0);
        System.out.println(sb);
    }
}
