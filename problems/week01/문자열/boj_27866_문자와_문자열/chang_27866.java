import java.io.*;
public class chang_27866 {
    public  static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String text = br.readLine();
        int index = Integer.parseInt(br.readLine());

        char result = text.charAt(index-1);
        System.out.println(result);
    }
}
