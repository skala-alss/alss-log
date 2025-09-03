import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_23881 {
    static int[] arr;

    static void selectionSort(int[] arr, int n, int k){
        int count = 0;
        for (int i = n - 1; i > 0; i--) {
            int maxIndex = i;
            for (int j = 0; j < i; j++) {
                if (arr[j] > arr[maxIndex]) maxIndex = j;
            }
            if (maxIndex == i) continue;

            count++;
            if (count == k) {
                System.out.println(arr[i] + " " + arr[maxIndex]);
                return;
            }
            swap(arr, maxIndex, i);
        }
        System.out.println(-1);
    }


    static void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());
        arr = new int[N];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<N;i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }
        selectionSort(arr,N,K);
    }
}
