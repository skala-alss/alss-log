import java.io.*;

public class donggeon_24389 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int input = Integer.parseInt(br.readLine());
        int input2comp = ~input + 1;  //2의 보수
        int diffBit = input ^ input2comp;
        System.out.println(Integer.bitCount(diffBit));  //서로 다른 비트수
    }
}