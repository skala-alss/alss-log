import java.io.*;

public class chang_2501 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] t = br.readLine().trim().split("\\s+"); // "N K"
        int N = Integer.parseInt(t[0]);
        int K = Integer.parseInt(t[1]);

        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            if (N % i == 0) {      // i가 약수면
                cnt++;
                if (cnt == K) {    // K번째 약수면 출력하고 종료
                    System.out.println(i);
                    return;
                }
            }
        }
        System.out.println(0);     // K번째 약수가 없으면 0
    }
}
