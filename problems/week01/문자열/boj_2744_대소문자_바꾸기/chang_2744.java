import java.util.Scanner;

public class chang_2744 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String word = sc.next();
        StringBuilder result = new StringBuilder();

        for (char c : word.toCharArray()) {
            if (Character.isUpperCase(c)) {
                result.append(Character.toLowerCase(c));
            } else if (Character.isLowerCase(c)) {
                result.append(Character.toUpperCase(c));
            }
        }

        System.out.println(result.toString());
        sc.close();

    }
}
