import java.util.Scanner;

public class donggeon_5597 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        //학생 배열
        int[] students = new int[30];
        for (int i = 0; i < students.length; i++) {
            students[i] = i + 1;
        }

        //과제를 제출한 학생 배열
        int[] submitters = new int[28];
        for (int i = 0; i < 28; i++) {
            submitters[i] = scanner.nextInt();
        }

        //students 중 submitters가 아닌 것 찾기
        int[] nonSubmitters = new int[2];
        int pos = 0;

        for (int i = 0; i < students.length; i++) {
            for (int j = 0; j < submitters.length; j++) {
                if (students[i] == submitters[j]) {
                    break;
                }
                if ((j == submitters.length - 1) && (students[i] != submitters[j])) {
                    nonSubmitters[pos] = students[i];
                    pos++;
                }
            }
        }

        //출력
        for (int nonSubmitter : nonSubmitters) {
            System.out.println(nonSubmitter);
        }
    }
}

//import java.util.HashSet;
//import java.util.Scanner;
//import java.util.Set;
//
//public class donggeon_5597 {
//    public static void main(String[] args) {
//        Scanner scanner = new Scanner(System.in);
//
//        // 제출한 학생 번호 저장할 Set
//        Set<Integer> submitters = new HashSet<>();
//
//        for (int i = 0; i < 28; i++) {
//            submitters.add(scanner.nextInt());
//        }
//
//        // 1~30번 학생 중 제출 안 한 학생 찾기
//        for (int i = 1; i <= 30; i++) {
//            if (!submitters.contains(i)) {
//                System.out.println(i);
//            }
//        }
//    }
//}