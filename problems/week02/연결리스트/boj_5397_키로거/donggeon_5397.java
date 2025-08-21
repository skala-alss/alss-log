import java.io.*;
import java.util.LinkedList;
import java.util.StringTokenizer;
import java.util.ListIterator;

public class donggeon_5397 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        int count = Integer.parseInt(br.readLine());
        for (int i = 0; i < count; i++) {
            LinkedList<Character> list = new LinkedList<>();
            ListIterator<Character> it = list.listIterator();

            String strInput = br.readLine();
            for (int j = 0; j < strInput.length(); j++) {
                char target = strInput.charAt(j);
                //if (('a' <= target) && (target <= 'z') ||
                //        ('A' <= target) && (target <= 'Z'))
                if ((Character.isAlphabetic(target) && target <= 127) ||
                        (Character.isDigit(target))) {
                    it.add(target);
                } else if (target == '<') {
                    if (it.hasPrevious()) {
                        it.previous();
                    }
                } else if (target == '>') {
                    if (it.hasNext()) {
                        it.next();
                    }
                } else if (target == '-') {
                    if (it.hasPrevious()) {
                        it.previous();
                        it.remove();
                    }
                }
            }
            for (char c : list) {
                sb.append(c);
            }
            sb.append("\n");
        }

        System.out.print(sb.toString());
    }
}