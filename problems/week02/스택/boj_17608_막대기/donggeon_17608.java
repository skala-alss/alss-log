import java.io.*;
import java.util.ArrayDeque;
import java.util.Deque;

public class donggeon_17608 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = Integer.parseInt(br.readLine());

        Deque<Integer> dq = new ArrayDeque<>();
        for (int i = 0; i < count; i++) {
            dq.push(Integer.parseInt(br.readLine()));
        }

        int showedBlockCnt = 0;  //보이는 블럭 수 카운트
        int rh = 0;  //reference height: 비교대상 높이
        for (int i = 0; i < count; i++) {
            int popItem = dq.pop();
            if (rh < popItem) {
                rh = popItem;
                showedBlockCnt++;
            }
        }

        System.out.println(showedBlockCnt);
    }
}
