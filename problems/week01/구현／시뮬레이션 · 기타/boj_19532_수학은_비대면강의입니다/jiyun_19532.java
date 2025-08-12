//package week01.구현／시뮬레이션 · 기타.boj_19532_수학은_비대면강의입니다;
import java.util.*;

public class jiyun_19532 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        int c = sc.nextInt();
        int d = sc.nextInt();
        int e = sc.nextInt();
        int f = sc.nextInt();

        for ( int x = -999 ; x <1000 ; x++){
            for (int y=-999;y<1000;y++){
                if(a*x+b*y==c && d*x+e*y==f ){
                    System.out.println(x +" "+y);
                    return;
                }
            }
        }
    }
}