import java.io.*;
import java.util.*;

public class chang_23899 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        // N 입력
        int N = Integer.parseInt(br.readLine());

        // 배열 A 입력
        int[] A = new int[N];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            A[i] = Integer.parseInt(st.nextToken());
        }

        // 배열 B 입력
        int[] B = new int[N];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            B[i] = Integer.parseInt(st.nextToken());
        }
        if (Arrays.equals(A,B)){
            System.out.println(1);
            return;
        }
        // 선택 정렬 시뮬레이션
        for (int last = N - 1; last > 0; last--) {
            // 1. [0..last] 중 최댓값 찾기
            int maxIdx = 0;
            for (int i = 1; i <= last; i++){
                if (A[i] > A[maxIdx]) maxIdx = i;
            }

            if(last != maxIdx){
                int tmp = A[last];
                A[last] = A[maxIdx];
                A[maxIdx] = tmp;
            }

            if (Arrays.equals(A,B)) {
                System.out.println(1);
                return;
            }




        }

        System.out.println(0);
    }
}
