//BigIntger는 배열 형태로 숫자의 자릿수를 저장하면서 연산하기 때문에
//기본 타입보다 훨씬 큰 정수를 다룰 수 있음
//다만 int 리터럴 대신 BigInteger 상수를 이용해야 하며,
//반드시 일반 연산자가 아닌 메서드 연산자를 이용해야 함
import java.io.*;
import java.math.BigInteger;

public class donggeon_27434 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());
        System.out.println(factorial(1, N));
    }

    //값이 매우 크므로 StackOverflow 발생 주의
    //특히 팩토리얼은 누적 곱셈이므로 뒤로 갈수록 값이 커져 느려지므로 분할 정복 이용하면 성능이 개선됨
    public static BigInteger factorial(int start, int end) {
        BigInteger value = BigInteger.ONE;
        if (start > end) {
            return value;
        }
        if (start == end) {
            return BigInteger.valueOf(start);
        }

        int mid = (start + end) / 2;
        return factorial(start, mid).multiply(factorial(mid + 1, end));
    }
}