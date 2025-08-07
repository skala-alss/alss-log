import java.io.*;

public class donggeon_10871 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int count = Integer.parseInt(input[0]);
        int num = Integer.parseInt(input[1]);

        int[] arr = new int[count];
        String[] arrInput = br.readLine().split(" ");
        for (int i = 0; i < count; i++) {
            arr[i] = Integer.parseInt(arrInput[i]);
            if (arr[i] < num) {
                System.out.print(arr[i] + " ");
            }
        }
    }
}
