import java.io.*;

public class jiyun_30204 {
    public static void main(String[] args) throws IOException {
        // 두번째 줄 모두 합 % X == 0 -> 출력 1
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String[] tokens = br.readLine().split(" ");
        int N = Integer.parseInt(tokens[0]);
        int X = Integer.parseInt(tokens[1]);

        int sum=0;
        String[] people = br.readLine().split(" ");
        for(int i=0;i<N;i++){
            sum += Integer.parseInt(people[i]);
        }

        if(sum % X == 0){
            System.out.println(1);
        } else{
            System.out.println(0);
        }
    }
}
