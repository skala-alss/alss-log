import java.util.Queue;
import java.util.LinkedList;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class chang_2161 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine().trim());

        Queue<Integer> queue = new LinkedList<>();
        for(int a = 1; a <= N; a++){
            queue.offer(a);
        }

        StringBuilder sb = new StringBuilder();

        while (queue.size() > 1){
            sb.append(queue.poll()).append(" ");
            queue.offer(queue.poll());
        }
        sb.append(queue.peek());

        System.out.println(sb.toString());
    }
}
