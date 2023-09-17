import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class FiveIntegers {
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		int N = 5;
		Set<Integer> hs = new HashSet<>();
		int cnt = 0;
		while(N-->0) {
			if(hs.add(in.nextInt())) {
				cnt++;
			}
		}
		System.out.println(cnt);
	}
}
