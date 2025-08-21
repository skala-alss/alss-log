import java.io.*;

public class donggeon_10820 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        String str;

        while ((str = br.readLine()) != null) {
            int lowerCnt = 0;
            int upperCnt = 0;
            int numCnt = 0;
            int spaceCnt = 0;

            for (int i = 0; i < str.length(); i++) {
                char c = str.charAt(i);
                if (Character.isDigit(c)) {
                    numCnt++;
                } else if (c == ' ') {
                    spaceCnt++;
                } else {
                    if (Character.isLowerCase(c)) {
                        lowerCnt++;
                    } else {
                        upperCnt++;
                    }
                }
            }
            sb.append(lowerCnt).append(" ").append(upperCnt).append(" ")
                    .append(numCnt).append(" ").append(spaceCnt).append("\n");
        }

        System.out.print(sb.toString());
    }
}
