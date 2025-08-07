import java.io.*;

public class jiyun_2480 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] tokens = br.readLine().split(" ");

        int a = Integer.parseInt(tokens[0]);
        int b = Integer.parseInt(tokens[1]);
        int c = Integer.parseInt(tokens[2]);

        int price;

        if( a==b && b==c){
            price=10000+a*1000;
        } else if(a==b || a==c){
            price=1000+a*100;
        } else if(b==c){
            price=1000+b*100;
        } else {
            price=Math.max(Math.max(a,b),c) *100;
        }
        System.out.println(price);
    }
}
