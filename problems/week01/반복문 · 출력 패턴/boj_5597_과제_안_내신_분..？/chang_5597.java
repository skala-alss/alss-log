import java.io.*;
import java.util.*;
public class chang_5597 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        ArrayList<Integer> list = new ArrayList<>();

        for (int i =0; i< 28; i++){
            int n = Integer.parseInt(br.readLine());
            list.add(n);
        }

        for (int i =1; i<= 30; i++){
            if(!list.contains(i)){
                System.out.println(i);
            }
        }
    }
}
