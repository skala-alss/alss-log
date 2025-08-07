import java.io.*;

public class donggeon_10950 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int count = Integer.parseInt(br.readLine());
        int[] numberSum = new int[count];

        for (int i = 0; i < count; i++) {
            String[] numbers = br.readLine().split(" ");
            int num1 = Integer.parseInt(numbers[0]);
            int num2 = Integer.parseInt(numbers[1]);

            numberSum[i] = num1 + num2;
        }

        for (int sum : numberSum) {
            System.out.println(sum);
        }
    }
}
