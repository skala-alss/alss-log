import java.io.*;
import java.util.*;
public class chang_10250 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        int T = Integer.parseInt(br.readLine());

        for (int i = 0; i < T; i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int H = Integer.parseInt(st.nextToken());
            int W = Integer.parseInt(st.nextToken());
            int N = Integer.parseInt(st.nextToken());

            int Y = N % H;
            int X = N / H + 1;

            if (Y==0){
                Y = H;
                X = N /H;
            }
            int roomNumber = Y * 100 + X;

            sb.append(roomNumber).append("\n");
        }
        System.out.println(sb);
    }
}
