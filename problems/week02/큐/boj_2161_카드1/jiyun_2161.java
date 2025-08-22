import java.io.*;
import java.util.Queue;
import java.util.ArrayDeque;

public class jiyun_2161 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
        int n = Integer.parseInt(br.readLine());

        Queue<Integer> queue = new ArrayDeque<>();
        for(int i=1;i<=n;i++) {
            queue.offer(i);
        }

        StringBuilder sb = new StringBuilder();
        while(queue.size()>1){
//           첫번째 카드를 버린다
            sb.append(queue.poll()).append(' ');
//           그리고 제일 위에 있는 카드를 맨 뒤로 보낸다.
            queue.offer(queue.poll());
        }
        //마지막 카드 붙이기
        sb.append(queue.poll());
        System.out.println(sb.toString());
    }
}
