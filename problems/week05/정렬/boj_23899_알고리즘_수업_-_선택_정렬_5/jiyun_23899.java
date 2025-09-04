import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.Arrays;

public class jiyun_23899 {
    static int[] arr1;
    static int[] arr2;

    static int selectSort(int[] A,int[] B, int n){
        if(Arrays.equals(A,B)) return 1;

        for (int i=n-1;i>0;i--){
            int maxIndex = 0;
            for (int j=1;j<=i;j++){
                if(A[j]> A[maxIndex]){
                    maxIndex = j;
                }
            }
            if(maxIndex != i){
                int temp = A[i];
                A[i] = A[maxIndex];
                A[maxIndex] = temp;
                if(Arrays.equals(A,B)) return 1;
            }
        }
        return Arrays.equals(A,B) ? 1 : 0;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());
        arr1 = new int[N];
        arr2 = new int[N];

        StringTokenizer st = new StringTokenizer(br.readLine());
        for(int i=0;i<N;i++){
               arr1[i] = Integer.parseInt(st.nextToken());
        }
        st = new StringTokenizer(br.readLine());
        for(int i=0;i<N;i++){
            arr2[i] = Integer.parseInt(st.nextToken());
        }

        System.out.println(selectSort(arr1,arr2,N));
    }
}
