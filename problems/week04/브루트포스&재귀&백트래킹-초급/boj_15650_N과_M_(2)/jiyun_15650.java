import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_15650 {
    static int n,m;

    static void Backtracking(int depth, int start, String str){
        // 종료조건
        if(depth==m){
            System.out.println(str);
            return;
        }
        for(int j=start;j<=n;j++){
            Backtracking(depth+1, j+1, str + j + " ");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        Backtracking(0,1, "");
    }
}

