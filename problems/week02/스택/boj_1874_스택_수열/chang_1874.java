import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
public class chang_1874 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());

        Stack<Integer> stack = new Stack<>();
        StringBuilder sb = new StringBuilder();
        int next = 1;

        for(int i=0; i<n; i++){
            int target = Integer.parseInt(br.readLine().trim());

            while (next<=target){
                stack.push(next++);
                sb.append("+\n");
            }
            if (stack.isEmpty() || stack.peek() != target) {
                System.out.println("NO");
                return;

            }

            stack.pop();
            sb.append("-\n");
        }

        System.out.println(sb.toString());
    }
}
