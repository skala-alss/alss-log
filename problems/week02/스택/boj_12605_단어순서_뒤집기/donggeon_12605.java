import java.io.*;
import java.util.StringTokenizer;
import java.util.ArrayDeque;

// 1. StringTokenizer 이용 방식
public class donggeon_12605 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        ArrayDeque<String> stack = new ArrayDeque<>();
        int count = Integer.parseInt(br.readLine());
        for (int i = 0; i < count; i++) {
            String strInput = br.readLine();
            StringTokenizer st = new StringTokenizer(strInput);
            //토큰의 남은 여부를 nextToken() 조건 비교가 아니라 hasMoreTokens()로 처리 가능
            while (st.hasMoreTokens()) {
                stack.push(st.nextToken());
            }

            int stackSize = stack.size();  //stackSize 저장
            bw.write("Case #" + (i + 1) + ": ");  //출력 구조문
            for (int j = 0; j < stackSize; j++) {
                bw.write(stack.pop() + " ");
            }
            bw.write("\n");  //줄넘김
        }

        bw.flush();
        bw.close();
    }
}
