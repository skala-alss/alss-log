import java.io.*;

public class java_2798 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] NM_tokens = br.readLine().split(" ");

        int N = Integer.parseInt(NM_tokens[0]);
        int M = Integer.parseInt(NM_tokens[1]);

        int[] arr = new int[N];
        String[] Card_tokens = br.readLine().split(" ");
        for(int i=0;i< Card_tokens.length;i++){
            arr[i] = Integer.parseInt(Card_tokens[i]);
        }

        int max =0;

        for (int i = 0; i < N - 2; i++) {
            for (int j = i + 1; j < N - 1; j++) {
                for (int k = j + 1; k < N; k++) {
                    int sum = arr[i] + arr[j] + arr[k];
                    if (sum <= M && sum > max) {
                        max = sum;
                    }
                }
            }
        }
        System.out.println(max);
    }
}
