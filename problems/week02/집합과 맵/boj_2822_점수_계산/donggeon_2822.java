import java.io.*;
import java.util.*;
import java.util.Collections;

public class donggeon_2822 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        TreeMap<Integer, Integer> map = new TreeMap<>(Collections.reverseOrder());
        for (int i = 1; i <= 8; i++) {
            int score = Integer.parseInt(br.readLine());
            //점수가 다 다르다고 하였고, 합이 아닌 직접 나열해야 할 것은 문제번호이므로
            //key에 점수를, value에 문제 번호를 넣었음
            map.put(score, i);
        }

        int scoreSumTop5 = 0;           //상위 5개 점수 합 변수
        int[] problemSeq = new int[5];  //문제 번호 담을 배열

        int idx = 0;
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            if (idx == 5) {
                break;
            }
            scoreSumTop5 += entry.getKey();
            problemSeq[idx] = entry.getValue();
            idx++;
        }
        //Collections.sort는 List 타입만 정렬 가능하고, 배열은 Arrays.sort 사용
        Arrays.sort(problemSeq);

        System.out.println(scoreSumTop5);
        for (int i : problemSeq) {
            System.out.print(i + " ");
        }
    }
}
