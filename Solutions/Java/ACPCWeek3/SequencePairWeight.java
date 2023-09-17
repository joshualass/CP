import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class SequencePairWeight {
	public static int n;
	public static int s;
	public static int m;
	public static int[] arr;
	public static Set<Integer> set;
	public static void recur(int index, int count) {
		if(index < 0) {
			System.out.println("left");
			System.out.println(count);
			return;
		}
		if(index > arr.length-1) {
			System.out.println("right");
			System.out.println(count);
			return;
		}
		if(m == arr[index]) {
			System.out.println("magic");
			System.out.println(count);
			return;
		}
		if(set.add(index)) {
			recur(index + arr[index],count + 1);
		} else {
			System.out.println("cycle");
			System.out.println(count);
		}
		
	}
	
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		
		n = in.nextInt(); //number squares
		s = in.nextInt(); //start
		m = in.nextInt(); //magic number
		
		in.nextLine();
		
		String[]hold = in.nextLine().trim().split(" ");
		arr = new int[n];
		for(int i = 0; i < n; i++) {
			arr[i] = Integer.parseInt(hold[i]);
		}
		set = new HashSet<>();
		recur(s-1,0);
		
	}
}
