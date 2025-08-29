import java.util.Deque;
import java.util.ArrayDeque;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class chang_10866 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine().trim());

        Deque<Integer> deque = new ArrayDeque<>();
        StringBuilder sb = new StringBuilder();

        for(int i=1; i<=N; i++){
            String line = br.readLine().trim().trim();
            if(line.startsWith("push_front")){
                int x = Integer.parseInt(line.split(" ")[1]);
                deque.addFirst(x);
            }else if(line.startsWith("push_back")){
                int x = Integer.parseInt(line.split(" ")[1]);
                deque.addLast(x);
            }else if(line.equals("pop_front")){
                Integer v = deque.pollFirst();
                sb.append(v == null ? -1 : v).append('\n');
            }else if(line.equals("pop_back")){
                Integer v = deque.pollLast();
                sb.append(v == null ? -1 : v).append('\n');
            }else if(line.equals("size")){
                sb.append(deque.size()).append('\n');
            }else if(line.equals("empty")){
                sb.append(deque.isEmpty() ? 1 : 0).append('\n');
            }else if (line.equals("front")){
                Integer v = deque.peekFirst();
                sb.append(v == null ? -1 : v).append('\n');
            }else if(line.equals("back")){
                Integer v = deque.peekLast();
                sb.append(v == null ? -1 : v).append('\n');
            }
        }
        System.out.println(sb.toString());
    }
}
