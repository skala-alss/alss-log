import java.io.*;
import java.util.*;

public class jiyun_1927 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PriorityQueue<Integer> pq = new PriorityQueue<>();

        int n = Integer.parseInt(br.readLine()); //연산의 개수

        StringBuilder sb = new StringBuilder();

        for(int i=0;i<n;i++){
            int x = Integer.parseInt(br.readLine());

            if(x!=0){
                pq.add(x);
            } else {
                if(pq.isEmpty()) sb.append(0).append('\n');
                else sb.append(pq.poll()).append('\n');
            }
        }
        System.out.println(sb.toString());
    }
}
