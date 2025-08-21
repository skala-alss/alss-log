import java.util.*;
import java.io.*;

 class jiyun_1406 {
    public static void main(String[] args) throws IOException {
       BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
       String input = br.readLine();;
       int n = Integer.parseInt(br.readLine());

       // linkedlist에 값 넣기
       LinkedList<Character> list = new LinkedList<>();
       for(int i=0;i<input.length();i++){
           list.add(input.charAt(i));
       }
       // 커서 왼쪽 오른쪽 이동 -> 양방향 연결 리스트
       ListIterator<Character> cursor = list.listIterator(list.size());
       for(int j=0;j<n;j++){
           StringTokenizer st = new StringTokenizer(br.readLine());
            String command = st.nextToken();

            switch (command){
                case "L":{
                    if(cursor.hasPrevious()) cursor.previous();
                    break;
                }
                case "D":{
                    if(cursor.hasNext()) cursor.next();
                    break;
                }
                case "B":{
                    if(cursor.hasPrevious()){
                       cursor.previous();
                       cursor.remove();
                   }
                   break;
                }
                case "P":{
                    char word = st.nextToken().charAt(0);
                    cursor.add(word);
                    break;
                }
            }
       }
        StringBuilder sb = new StringBuilder(list.size());
        for (char c : list) sb.append(c);
        System.out.println(sb.toString());
    }
}
