import java.io.*;
public class chang_2292 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        int count = 1;
        int maxNum = 1;

        while (n > maxNum) {
            maxNum += 6*count;
            count++;
        }
        System.out.println(count);
    }
}
