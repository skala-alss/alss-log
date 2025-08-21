import java.io.*;
import java.util.StringTokenizer;
import java.util.TreeSet;
import java.util.Comparator;  //Treeset 역순 정렬

public class donggeon_7785 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        int count = Integer.parseInt(br.readLine());
        TreeSet<String> employees = new TreeSet<>(Comparator.reverseOrder());
        for (int i = 0; i < count; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            String name = st.nextToken();
            String state = st.nextToken();

            if (state.equals("enter")) {
                employees.add(name);
            } else if (state.equals("leave")) {
                employees.remove(name);
            }
        }

        for (String employee : employees) {
            sb.append(employee).append("\n");
        }
        System.out.print(sb.toString());
    }
}
