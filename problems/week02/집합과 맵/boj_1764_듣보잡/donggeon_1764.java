import java.io.*;
import java.util.StringTokenizer;
import java.util.Set;
import java.util.HashSet;
import java.util.TreeSet;

public class donggeon_1764 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        Set<String> notListened = new HashSet<>();
        Set<String> notSeen = new HashSet<>();
        Set<String> notListenedAndSeen = new TreeSet<>();  // 사전 순 출력 요청 -> TreeSet

        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());  // 듣지도 못한 사람 수
        int m = Integer.parseInt(st.nextToken());  // 보지도 못한 사람 수

        // 듣지도 못한 사람 set
        for (int i = 0; i < n; i++) {
            notListened.add(br.readLine());
        }
        // 보지도 못한 사람 set
        for (int i = 0; i < m; i++) {
            notSeen.add(br.readLine());
        }
        // 듣보잡
        int minNumber = Math.min(n, m);  // 작은 set 내역이 상대 set에 있는지 확인
        if (minNumber == n) {
            for (String name : notListened) {
                if (notSeen.contains(name)) {
                    notListenedAndSeen.add(name);
                }
            }
        } else {
            for (String name : notSeen) {
                if (notListened.contains(name)) {
                    notListenedAndSeen.add(name);
                }
            }
        }

        System.out.println(notListenedAndSeen.size());
        for (String name : notListenedAndSeen) {
            System.out.println(name);
        }
    }
}
