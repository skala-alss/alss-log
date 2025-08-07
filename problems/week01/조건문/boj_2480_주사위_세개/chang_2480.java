import java.util.Scanner;

public class chang_2480 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int M = sc.nextInt();
        int K = sc.nextInt();

        if(N==M && M==K){
            System.out.println(10000+N*1000);
        }else if(N==M||N==K){
        System.out.println(1000+N*100);
        }else if(M==K){
            System.out.println(1000+M*100);
        }   else{
            System.out.println(Math.max(N, Math.max(M, K)) * 100);

        }
    }
}
