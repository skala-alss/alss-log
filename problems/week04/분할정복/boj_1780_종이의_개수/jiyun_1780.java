package boj_1780_종이의_개수;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.Arrays;

public class jiyun_1780 {
    static int[][] arr;
    static int[] answer;

    static void mergeSort(int row, int col, int n){
        if(check(row,col,n)){
            answer[arr[row][col]+1]++;
            return;
        }
        int size = n/3;

        mergeSort(row,col,size); //1
        mergeSort(row,col+size,size);//2
        mergeSort(row,col+size*2,size);//3

        mergeSort(row+size,col,size);//4
        mergeSort(row+size,col+size,size);//5
        mergeSort(row+size,col+size*2,size);//6


        mergeSort(row+size*2,col,size);  // 7
        mergeSort(row+size*2,col+size,size); //8
        mergeSort(row+size*2,col+size*2,size); //9
    }

    //row,col은 시작좌표
    static boolean check(int row, int col,int n){
        int firstBlock = arr[row][col];

        for(int i=row;i<row+n;i++){
            for(int j=col; j<col+n; j++){
                if(firstBlock !=arr[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        answer = new int[3];
        arr = new int[n][n];

        for(int i=0;i<n;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            for(int j=0;j<n;j++){
                arr[i][j] = Integer.parseInt(st.nextToken());
            }
        }
        mergeSort(0,0,n);
        System.out.println(answer[0]);
        System.out.println(answer[1]);
        System.out.println(answer[2]);
    }
}
