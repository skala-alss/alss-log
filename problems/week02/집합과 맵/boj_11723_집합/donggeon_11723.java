import java.io.*;
import java.util.Set;
import java.util.HashSet;
import java.util.StringTokenizer;

public class donggeon_11723 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        Set<Integer> set = new HashSet<>();
        StringBuilder sb = new StringBuilder();  //결과 누적용
        int count = Integer.parseInt(br.readLine());

        for (int i = 0; i < count; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            String order = st.nextToken();
            int num;
            switch (order) {
                case "add":
                    num = Integer.parseInt(st.nextToken());
                    set.add(num);
                    break;
                case "remove":
                    num = Integer.parseInt(st.nextToken());
                    set.remove(num);
                    break;
                case "check":
                    num = Integer.parseInt(st.nextToken());
                    sb.append(set.contains(num) ? 1 : 0).append("\n");
                    break;
                case "toggle":
                    num = Integer.parseInt(st.nextToken());
                    if (set.contains(num)) { set.remove(num); }
                    else { set.add(num); }
                    break;
                case "all":
                    for (int e = 1; e <= 20; e++) {
                        set.add(e);
                    }
                    break;
                case "empty":
                    set.clear();
                    break;
            }
        }

        //한 번에 출력
        bw.write(sb.toString());
        bw.flush();  //버퍼에 쌓아둔 데이터 한 번에 강제 출력
        bw.close();  //스트림 닫기. 입력은 JVM이 자동정리해줌.
    }
}
