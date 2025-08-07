import java.util.Scanner;

public class donggeon_2738 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int M = scanner.nextInt();

        int[][] A = new int[N][M];
        int[][] B = new int[N][M];

        //행렬 A 원소 받기
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = scanner.nextInt();
            }
        }

        //행렬 B 원소 받기
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                B[i][j] = scanner.nextInt();
            }
        }

        //합행렬 원소 출력
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int num = A[i][j] + B[i][j];
                System.out.print(num + " ");
            }
            System.out.println();
        }
    }
}