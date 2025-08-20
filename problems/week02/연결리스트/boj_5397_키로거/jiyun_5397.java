// --------------
// 백준 문제 : 5397_키로거
// 작성자: 송지윤
// 첫째줄 : 테스트 케이스 , 한줄로 이루어짐, 길이: L
// 백스페이스 : - / 화살표 : < , > /
// 알파벳 대문자, 소문자, 숫자 -> 비밀번호의 일부
// --------------

import java.io.*;
import java.util.*;

public class jiyun_5397 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = Integer.parseInt(br.readLine());

        for(int i=0;i<count;i++){
            String input = br.readLine();
            LinkedList<Character> list = new LinkedList<>();
            ListIterator<Character> cursor = list.listIterator();

            for (char c : input.toCharArray()){
                if(c=='<'){
                    if(cursor.hasPrevious()) cursor.previous();
                } else if(c=='>'){
                    if(cursor.hasNext()) cursor.next();
                } else if(c=='-'){
                    if(cursor.hasPrevious()) {
                        cursor.previous();
                        cursor.remove();
                    }
                } else{
                    cursor.add(c);
                }
            }

            StringBuilder sb = new StringBuilder();
            for (char a : list) sb.append(a);
            System.out.println(sb.toString());
        }

    }
}
