import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_23969 {
    static int[] arr;
    static void bubbleSort(int[] arr, int n, int k){
        int count=0;
        for(int i=n-1;i>=1;i--){
            for(int j=0;j<i;j++){
                if(arr[j] > arr [j + 1]){
                    swap(arr,j,j+1);
                    count++;
                    if(count==k){
                        for (int x = 0; x < n; x++) {
                            System.out.printf("%d ", arr[x]);
                        }
                        System.out.println();
                        return;
                    }

                }
            }
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
        bubbleSort(arr,N,K);
    }
}
