import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
public class chang_10828 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());

        Stack<Integer> stack = new Stack<>();
        StringBuilder out = new StringBuilder();

        for(int i =1; i<=n; i++) {
            String line = br.readLine().trim();

            if(line.startsWith("push")) {
                int x = Integer.parseInt(line.split(" ")[1]);
                stack.push(x);
            }else if(line.equals("pop")) {
                out.append(stack.isEmpty() ? -1 : stack.pop()).append('\n');
            }else  if(line.equals("size")) {
                out.append(stack.size()).append('\n');
            }else if(line.equals("empty")) {
                out.append(stack.isEmpty() ? 1 : 0).append('\n');
            }else if (line.equals("top")){
                out.append(stack.isEmpty() ? -1 : stack.peek()).append('\n');
            }
        }
        System.out.print(out.toString());
    }
}
