import java.io.*;
import java.util.*;

public class donggeon_1940 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int m = Integer.parseInt(br.readLine());
        //int[] arr = new int[n];

        ArrayList<Integer> list = new ArrayList<Integer>();
        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++) {
            //arr[i] = Integer.parseInt(st.nextToken());
            list.add(Integer.parseInt(st.nextToken()));
        }
        
        int cnt = 0;  // 만들 수 있는 갑옷 개수
        Collections.sort(list);
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int sum = list.get(left) + list.get(right);
            if (sum < m) {
                sum -= list.get(left);
                left++;
            } else if (sum > m) {
                sum -= list.get(right);
                right--;
            } else {
                cnt++;
                left++;
            }
        }

        System.out.println(cnt);
    }
}
