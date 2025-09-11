import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class jiyun_27434 {
    public static BigInteger factorial(int a, int n) {

        BigInteger mul = BigInteger.valueOf(a);

        // 각 구간을 반으로 나누어 계산한 후에 곱하는 방법으로 처리 -> 구간곱으로 바꿔서 계산
        // 작은 수끼리 먼저 곱해 중간 결과 크기를 천천히 키워가기 때문에, 매번 "큰 수 × 작은 수" 연산보다 훨씬 효율적.
        if(a < n) {
            int b = (a + n) / 2;
            mul = factorial(a, b).multiply(factorial(b + 1, n));
        }

        return mul;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        System.out.println(factorial(1, n));
    }
}
