import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class donggeon_9086 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = Integer.parseInt(br.readLine());

        for (int i = 1; i <= count; i++) {
            String input = br.readLine();
            String result = input.substring(0, 1) + input.substring(input.length() - 1);
            System.out.println(result);
        }
    }
}
