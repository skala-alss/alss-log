import java.io.*;

public class jiyun_10809 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();

        int[] arr = new int[26];

        for(int i=0;i<arr.length;i++){
            arr[i]=-1;
        }
        for(int i = 0; i<input.length();i++){
            char c = input.charAt(i);

            if(arr[c - 'a'] == -1){
                arr[c - 'a'] = i;
            }
        }
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if (i < arr.length - 1) System.out.print(" ");
        }
        System.out.println();
    }
}
