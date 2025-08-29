import java.io.*;
public class chang_23251 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < T; i++) {
            long k = Long.parseLong(br.readLine());
            sb.append(23*k).append('\n');
        }


        System.out.println(sb);

        }
    }

