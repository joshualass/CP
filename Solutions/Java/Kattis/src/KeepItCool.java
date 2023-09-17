import java.util.Scanner;

public class KeepItCool {
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int stud = in.nextInt();
		int slot = in.nextInt();
		int c = in.nextInt();
		in.nextLine();
		String [] arr = in.nextLine().trim().split(" ");
		int[] f = new int[arr.length];
//		ArrayList<Slot> 
		for(int i = 0; i < f.length; i++) {
			f[i] = Integer.parseInt(arr[i]);
		}
		
		
		
	}
}
