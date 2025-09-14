import java.io.*;
import java.util.StringTokenizer;
import java.util.Set;
import java.util.HashSet;

public class donggeon_10815 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));;
        StringTokenizer st;
        StringBuilder sb = new StringBuilder();
        Set<Integer> set = new HashSet<>();

        int n = Integer.parseInt(br.readLine());  // 상근이가 가지고 있는 숫자 카드 개수
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {             // 상근이가 가진 숫자 카드
            set.add(Integer.parseInt(st.nextToken()));
        }

        int m = Integer.parseInt(br.readLine());  // 상근이한테 확인해야 할 숫자 카드 개수
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < m; i++) {
            int target = Integer.parseInt(st.nextToken());
            sb.append(set.contains(target) ? 1 : 0).append(' ');
        }

        System.out.println(sb);
    }
}
