import java.util.Scanner;

public class BeautifulStrings {
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		int[] evens = new int[26];
		
		String line = in.next();
		for(int i = 0; i < line.length(); i++) {
			evens[line.charAt(i)-97] = evens[line.charAt(i)-97] + 1;
		}
		for(int i = 0; i < 26; i++) {
			if(evens[i] % 2 == 1) {
				System.out.println("No");
				return;
			}
		}
		System.out.println("Yes");
	}
}
