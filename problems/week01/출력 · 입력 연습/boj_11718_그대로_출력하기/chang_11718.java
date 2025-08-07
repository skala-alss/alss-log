import java.util.Scanner;

public class chang_11718 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {          // 더 이상 입력이 없을 때까지 반복
            String line = sc.nextLine();    // 한 줄 입력
            System.out.println(line);       // 그대로 출력
        }

        sc.close();
    }
}
