import java.io.*;
import java.util.ArrayDeque;

// 2. 배열과 정규표현식 이용 방식
public class donggeon_12605_2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        ArrayDeque<String> stack = new ArrayDeque<>();
        int count = Integer.parseInt(br.readLine());
        for (int i = 0; i < count; i++) {
            String strInput = br.readLine();
            //split은 내부적으로 분리된 토큰 수를 세서 그만큼의 배열을 동적으로 만들어 반환
            String[] arr = strInput.split(" ");
            for (int j = 0; j < arr.length; j++) {
                stack.push(arr[j]);
            }

            System.out.printf("Case #%d: ", (i + 1)); //Java의 printf문
            while (!stack.isEmpty()) {
                System.out.print(stack.pop() + " ");
            }
            System.out.println();
        }
    }
}
