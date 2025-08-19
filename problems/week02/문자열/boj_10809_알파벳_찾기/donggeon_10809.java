import java.io.*;

public class donggeon_10809 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        String input = br.readLine();

        for (char c = 'a'; c <= 'z'; c++) {
            //String.indexOf()는 값이 없으면 -1, 있으면 첫 등장 인덱스 반환
            int idx = input.indexOf(String.valueOf(c));
            bw.write(idx + " ");
        }

        bw.flush();
        bw.close();
    }
}
