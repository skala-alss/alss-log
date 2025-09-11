import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_15649 {
    static int n,m;
    static boolean flag[];

    static void Backtracking(int i, String str){
        // 종료조건
        if(i==m){
            System.out.println(str);
            return;
        }
        for(int j=1;j<=n;j++){
            if(!flag[j]){
                flag[j]=true;
                Backtracking(i+1,str+j+" ");
                flag[j]=false;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        flag = new boolean[n+1];
        Backtracking(0,"");
    }
}
