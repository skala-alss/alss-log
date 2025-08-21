import java.io.*;
import java.util.Queue;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class donggeon_26042 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int count = Integer.parseInt(br.readLine());
        Queue<Integer> q = new LinkedList<>();
        int maxLineCnt = 0;
        int lastStuId = 100000; // 작을 때 갱신되므로 max 값 부여

        for (int i = 0; i < count; i++) {
            String input = br.readLine();
            StringTokenizer st = new StringTokenizer(input);
            String order = st.nextToken();
            if (order.equals("1")) {
                int temp = Integer.parseInt(st.nextToken()); //일단 temp로 받고 삽입
                q.offer(temp);
                if (q.size() >= maxLineCnt) {  //줄이 maxLineCnt 이상으로 길어질 때
                    if (q.size() == maxLineCnt) {
                        if (temp < lastStuId) {
                            lastStuId = temp;
                        }
                    } else {
                        maxLineCnt = q.size();
                        lastStuId = temp;
                    }
                }
            } else if (order.equals("2")) {
                q.poll();
            }
        }
        System.out.println(maxLineCnt + " " + lastStuId);
    }
}
