import java.io.*;
import java.util.StringTokenizer;

public class donggeon_10807 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        int count = Integer.parseInt(br.readLine());
        int[] arr = new int[count];
        st = new StringTokenizer(br.readLine(), " ");
        for (int i = 0; i < count; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
        }
        int inputNum = Integer.parseInt(br.readLine());

        int sameCnt = 0;
        for (int number : arr) {
            if (number == inputNum) {
                sameCnt++;
            }
        }
        System.out.println(sameCnt);
    }
}
