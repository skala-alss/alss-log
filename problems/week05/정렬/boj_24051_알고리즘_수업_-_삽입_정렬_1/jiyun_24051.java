import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_24051 {
    static int[] arr;
    static void insertionSort(int[] arr, int n, int k){
        int count = 0;
        int answer = -1;

        // 문제 핵심은 만약 loc 뒤에 배열값이 앞에 값과 스왑이 일어나면 그때 저장 1회를 증가시키고 저장하는 것
        // 이때 만약 저장횟수와 문제에 주어진 K가 같다면 answer에 저장
        for(int i=1;i<n;i++){
            int j = i-1;
            int newItem = arr[i];
            while((0 <= j && newItem < arr[j])){
                arr[j+1] = arr[j];
                j--;
                count++;
                if(count==k){
                    answer = arr[j+1];
                }
            }
            if(j+1 != i){
                arr[j+1] = newItem;
                count++;
                if(count==k){
                    answer = arr[j+1];
                }
            }
        }
        System.out.println(answer);
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        arr = new int[n];

        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            arr[i] = Integer.parseInt(st.nextToken());
        }

        insertionSort(arr,n,k);
    }
}
