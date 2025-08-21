import java.io.*;

public class donggeon_11720 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int count = Integer.parseInt(br.readLine());
        String[] letters = br.readLine().split("");
        int[] arr = new int[letters.length];

        for (int i = 0; i < letters.length; i++) {
            arr[i] = Integer.parseInt(letters[i]);
        }

        int sum = 0;
        for (int num : arr) {
            sum += num;
        }
        System.out.println(sum);
    }
}
