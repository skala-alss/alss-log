import java.io.*;
import java.util.StringTokenizer;
import java.util.LinkedList;

public class donggeon_1406 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        // 문자열 입력
        String strInput = br.readLine();
        // 커서 왼쪽을 leftList, 커서 오른쪽을 rightList로 구분하여 생각
        LinkedList<String> leftList = new LinkedList<>();
        LinkedList<String> rightList = new LinkedList<>();
        // 초기 커서는 문장 맨 뒤에 위치하므로 leftList에 strInput 값 배치
        for (int i = 0; i < strInput.length(); i++) {
            leftList.addLast(String.valueOf(strInput.charAt(i)));
        }

        int count = Integer.parseInt(br.readLine());
        for (int i = 0; i < count; i++) {
            st = new StringTokenizer(br.readLine());
            String order = st.nextToken();
            if (order.equals("L")) {
                // left 뒤 문자를 right 앞으로
                if (leftList.isEmpty()) {  // 커서가 문장 맨 앞이면 무시
                    continue;
                }
                rightList.addFirst(leftList.removeLast());
            } else if (order.equals("D")) {
                // right 앞 문자를 left 뒤로
                if (rightList.isEmpty()) {  // 커서가 문장 맨 뒤면 무시
                    continue;
                }
                leftList.addLast(rightList.removeFirst());
            } else if (order.equals("B")) {
                // left 뒤 문자를 삭제
                if (leftList.isEmpty()) {  // 커서가 문장 맨 앞이면 무시
                    continue;
                }
                leftList.removeLast();
            } else if (order.equals("P")) {
                // 입력한 문자를 커서 왼쪽에 추가
                leftList.addLast(st.nextToken());
            }
        }

        // 출력할 문자열 합치기
        StringBuilder sb = new StringBuilder();
        for (String s : leftList) {
            sb.append(s);
        }
        for (String s : rightList) {
            sb.append(s);
        }
        System.out.println(sb.toString());  // StringBuilder는 내부적으로 char[]로 동작함
    }
}
