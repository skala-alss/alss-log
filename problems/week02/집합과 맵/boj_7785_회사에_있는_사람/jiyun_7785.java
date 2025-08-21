import java.util.*;
import java.io.*;


public class jiyun_7785 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Map<String, String> set = new HashMap<>();

        int n = Integer.parseInt(br.readLine());
        for(int i=0;i<n;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            String name = st.nextToken();
            String log = st.nextToken();

            if(set.containsKey(name)){
                set.remove(name);
            } else {
                set.put(name,log);
            }
        }
        List<String> list = new ArrayList<>(set.keySet());
        list.sort(Comparator.reverseOrder());

        StringBuilder sb = new StringBuilder();
        for (String name : list) sb.append(name).append('\n');
        System.out.print(sb);

    }
}
