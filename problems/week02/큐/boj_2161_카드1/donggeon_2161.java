import java.io.*;
import java.util.Queue;
import java.util.ArrayDeque;

public class donggeon_2161 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int num = Integer.parseInt(br.readLine());

        Queue<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < num; i++) {
            q.add(i + 1);
        }

        while (true) {
            int item = q.remove();
            System.out.print(item + " ");
            if (q.isEmpty()) {
                break;
            }
            int temp = q.remove();
            q.add(temp);
        }
    }
}
