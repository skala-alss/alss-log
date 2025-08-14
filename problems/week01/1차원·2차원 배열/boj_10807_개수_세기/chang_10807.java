import java.io.*;

public class chang_10807 {
    public  static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());
        String [] nums = br.readLine().split(" ");
        int target = Integer.parseInt(br.readLine());

        int count = 0;
                for(int i = 0; i < n; i++){
                    if (Integer.parseInt(nums[i]) == target){
                        count++;
                    }
                }
        System.out.println(count);
    }
}
