import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_23968 {
    static int[] arr;
    static void bubbleSort(int[] arr, int n, int k){
        int count =0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n-1;j++){
                if(arr[j] > arr [j + 1]) {
                    swap(arr, j, j + 1);
                    count++;
                }
                if(count==k){
                    System.out.printf("%d %d", arr[j], arr[j+1]);
                    return;
                }
            }
//            if (count == k) {
//                int lo = Math.min(x, y), hi = Math.max(x, y);
//                System.out.println(lo + " " + hi);
//                return;
//            }
        }
        System.out.println(-1);
    }
    static void swap(int[] arr,int i,int j){
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

        bubbleSort(arr,N,K);
    }
}
