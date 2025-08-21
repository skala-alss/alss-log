import java.util.*;
import java.io.*;

public class jiyun_11723 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Set<Integer> set = new HashSet<>();
        int m = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();

        for(int i=0;i<m;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            String command = st.nextToken();

            switch(command){
                case "add":{
                    set.add(Integer.parseInt(st.nextToken()));
                    break;
                }
                case "remove":{
                    set.remove(Integer.parseInt(st.nextToken()));
                    break;
                }
                case "check":{
                    int x = Integer.parseInt(st.nextToken());
                    if(set.contains(x)){
                        sb.append(1).append('\n');
                    } else {
                        sb.append(0).append('\n');
                    }
                    break;
                }
                case "toggle":{
                    int x = Integer.parseInt(st.nextToken());
                    if(set.contains(x)){
                        set.remove(x);
                    } else{
                        set.add(x);
                    }
                    break;
                }
                case "all":{
                    set.clear();
                    for(int a=1;a<=20;a++){
                        set.add(a);
                    }
                    break;
                }
                case "empty":{
                    set.clear();
                    break;
                }
            }

        }
        System.out.println(sb);
    }
}
