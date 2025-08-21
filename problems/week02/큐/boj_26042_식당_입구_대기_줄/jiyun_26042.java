import java.util.*;
import java.io.*;

public class jiyun_26042 {
    public static void main(String[] args) throws IOException{
        // TODO: 작성 시작
        // n개 -> 준비된 식사의 개수
        BufferedReader br  = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        Deque<Integer> queue = new ArrayDeque<>();
        int maxLen  = 0;
        int maxLast=0;
        for(int i=0;i<n;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int type=Integer.parseInt(st.nextToken());

            if(type==1){
                int people=Integer.parseInt(st.nextToken());
                queue.offer(people);

                int size = queue.size();
                int last = queue.peekLast();

                if(size > maxLen ) {
                    maxLen  = size;
                    maxLast = last;
                } else if(size==maxLen && last < maxLast){
                    maxLast = last;
                }

            } else {
                queue.poll();
            }
        }
        System.out.println(maxLen + " " + maxLast);
    }
}
