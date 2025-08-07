import java.io.*;
import java.util.*;

public class jiyun_2309 {
    public static void main(String[] args) throws IOException{
        // 전체의 키 합 - 두명의 난쟁이의 키 = 100
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        List<Integer> talls = new ArrayList<>();
        int sum=0;

        // 리스트에 키 담기
        for(int i=0;i<9;i++){
            int tall = Integer.parseInt(br.readLine());
            talls.add(tall);
            sum += tall;
        }

        for(int x=0;x<8;x++){
            for(int y=x+1;y<9;y++){
                if(sum - talls.get(x) -talls.get(y) == 100){
                    talls.remove(Math.max(x, y));
                    talls.remove(Math.min(x, y));

                    talls.sort((Comparator.naturalOrder()));
                    for(int tall :talls){
                        System.out.println(tall);
                    }
                    return;
                }
            }
        }

    }
}
