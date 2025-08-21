import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
public class chang_12605 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());

        for (int t= 1; t <= T; t++ ) {
            String[] words = br.readLine().trim().split(" ");
            Stack<String> stack = new Stack<>();

            for(String w : words)
                stack.push(w);


            StringBuilder sb = new StringBuilder();
            sb.append("Case #").append(t).append(": ");
            while (!stack.isEmpty()){
                sb.append(stack.pop());
                if (!stack.isEmpty()) sb.append(' ');
            }
            System.out.println(sb);
        }
    }
}
