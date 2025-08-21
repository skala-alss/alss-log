import java.util.Scanner;

public class donggeon_1094 {
    public static void main(String[] args) {
        // input: 40
        //0 -> 64
        //1 -> 32 32
        //2 -> 32 16
        //3 -> 32 8
        //4 -> 16 8 4 4
        //5 -> 16 8 4 2

        Scanner scanner = new Scanner(System.in);
        int x = scanner.nextInt();
        int length = 64; //길이 합
        int temp = 64;   //현재 길이
        int barCnt = 1;  //막대기 수

        if (x != 64) {
            while (true) {
                temp = temp >> 1;
                length -= temp;
                if (length < x) {
                    barCnt++;
                    length += temp;
                } else if (length == x) {
                    break;
                }
            }
        }

        System.out.println(barCnt);
    }
}
