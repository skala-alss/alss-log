import java.io.*;
public class chang_10870 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        int a =0, b =1;
        for (int i = 0; i < n; i++) {
            int temp = a+b;
            a=b;
            b=temp;
        }
        System.out.println(a);
    }
}
