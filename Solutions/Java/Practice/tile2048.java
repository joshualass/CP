import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class tile2048 {

	public static void maxMove(int [][] game, int row) {
		
		for(int col = 1; col < 4; col++) {
			int hold = col;
			while(hold >= 1 && game[row][hold-1] == 0) {
				game[row][hold-1] = game[row][hold];
				game[row][hold] = 0;
				hold--;
			}
		}
		
	}
	
	public static void move(int [][] game, int row) {
		
		boolean [] merge = {true,true,true};
		
		maxMove(game,row);
		
		for(int col = 1; col < 4; col++) {
			if(game[row][col] == game[row][col-1] && merge[col-1] == true) {
				game[row][col-1] = 2 * game[row][col];
				game[row][col] = 0;
				merge[col-1] = false;
				maxMove(game,row);
				
			} 
		}
		
	}
	public static void moveLeft(int [][] game) {
		for(int row = 0; row < 4; row++) {
			move(game, row);
		}
		
	}
	
	public static void rotateCC(int [][] game) {
		
		int [][] hold = new int [4][4];
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				hold [3 - col][row] = game[row][col];
			}
		}
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				game[row][col] = hold [row][col];
			}
		}
	}
	
	public static void rotateC(int [][] game) {
		int [][] hold = new int [4][4];
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				hold [col][3-row] = game[row][col];
			}
		}
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				game[row][col] = hold [row][col];
			}
		}
	}
	
	public static void rotate2(int [][] game) {
		
		int [][] hold = new int [4][4];
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				hold [3-row][3-col] = game[row][col];
			}
		}
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				game[row][col] = hold [row][col];
			}
		}
		
	}
	
	public static void main(String args []) throws FileNotFoundException {
		Scanner file = new Scanner(System.in);
		
		int [][] game = new int [4][4];
		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {
				game [row][col] = file.nextInt();
			}
			file.nextLine();
		}
		int direction = file.nextInt();
		if(direction == 0) {
			moveLeft(game);
		}
		if(direction == 1) {
			rotateCC(game);
			moveLeft(game);
			rotateC(game);
		}
		if(direction == 2) {
			rotate2(game);
			moveLeft(game);
			rotate2(game);
		}
		if(direction == 3) {
			rotateC(game);
			moveLeft(game);
			rotateCC(game);
		}
								
		for(int [] x: game) {
			for(int y: x) {
				System.out.print(y + " ");
			}
			System.out.println();
		} 
	}
}
