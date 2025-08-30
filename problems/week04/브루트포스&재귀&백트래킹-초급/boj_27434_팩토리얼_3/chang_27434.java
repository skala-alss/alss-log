import java.io.*;
import java.math.BigInteger;

public class chang_27434 {

    static BigInteger product(int lo, int hi) {
        if (lo > hi) return BigInteger.ONE;
        if (lo == hi) return BigInteger.valueOf(lo);


        if (hi - lo <= 32) {
            BigInteger res = BigInteger.ONE;
            for (int i = lo; i <= hi; i++) {
                res = res.multiply(BigInteger.valueOf(i));
            }
            return res;
        }

        int mid = (lo + hi) / 2 ;
        BigInteger left  = product(lo, mid);
        BigInteger right = product(mid + 1, hi);
        return left.multiply(right);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine().trim());

        if (N <= 1) {
            System.out.println(1);
            return;
        }
        System.out.println(product(2, N));
    }
}
