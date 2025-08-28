import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class jiyun_15654 {
    static int n,m;
    static int[] arr;
    static StringBuilder sb = new StringBuilder();
    static boolean flag[];
    static int[] result;

    static void Backtracking(int depth){
        // 종료조건
        if(depth==m){
            for(int i=0; i<m; i++) sb.append(result[i]).append(' ');
            sb.append('\n');
            return;
        }
        for(int i=0;i<n;i++){
            if(!flag[i]){
                flag[i] = true;
                result[depth] = arr[i];
                Backtracking(depth+1); // depth + 1
                flag[i] = false;
            }

        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        arr= new int[n];
        result = new int[m];
        flag = new boolean[n+1];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            int input = Integer.parseInt(st.nextToken());
            arr[i]=input;
        }
        Arrays.sort(arr);

        Backtracking(0);
        System.out.println(sb);
    }
}
