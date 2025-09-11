package boj_12891_DNA_비밀번호;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class jiyun_12891 {
    static void add(int[] curCount, char c ){
        if (c == 'A') curCount[0]++;
        else if (c == 'C') curCount[1]++;
        else if (c == 'G') curCount[2]++;
        else if (c == 'T') curCount[3]++;
    }
    static void remove(int[] curCount, char c){
        if (c == 'A') curCount[0]--;
        else if (c == 'C') curCount[1]--;
        else if (c == 'G') curCount[2]--;
        else if (c == 'T') curCount[3]--;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int totalStringCount = Integer.parseInt(st.nextToken());
        int useStringCount = Integer.parseInt(st.nextToken());

        String str = br.readLine();
        char[] arr = str.toCharArray();

        st = new StringTokenizer(br.readLine());
        int A = Integer.parseInt(st.nextToken());
        int C = Integer.parseInt(st.nextToken());
        int G = Integer.parseInt(st.nextToken());
        int T = Integer.parseInt(st.nextToken());

        int[] curCount = new int[4];
        int count = 0;

        //초기 윈도우
        for (int i = 0; i < useStringCount; i++) {
            add(curCount, str.charAt(i));
        }
        if(curCount[0] >=A && curCount[1] >= C && curCount[2] >= G && curCount[3] >=T) count++;
        // 움직이기
        for(int i = useStringCount;i<totalStringCount;i++){
            remove(curCount, str.charAt(i-useStringCount));
            add(curCount, str.charAt(i));
            if(curCount[0] >=A && curCount[1] >= C && curCount[2] >= G && curCount[3] >=T) count++;
        }
        System.out.println(count);
    }
}
