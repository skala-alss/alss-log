import java.io.*;

public class donggeon_11382 {
    public static void main(String[] args) throws IOException {
        //빠른 입력 받기
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        //한 줄로 입력받아 공백 기준으로 나누기
        String[] input = br.readLine().split(" ");

        //String -> Long 형변환
        long A = Long.parseLong(input[0]);
        long B = Long.parseLong(input[1]);
        long C = Long.parseLong(input[2]);

        System.out.println(A + B + C);
    }
}
