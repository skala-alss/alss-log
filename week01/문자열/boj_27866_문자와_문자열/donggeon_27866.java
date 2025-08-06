import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class donggeon_27866 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String word = br.readLine();
        int pos = Integer.parseInt(br.readLine());
        System.out.println(word.charAt(pos - 1));
    }
}
