import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Two {
	public static void main(String[] args) throws IOException {
		
		long total = 0;
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		for(int i = 0; i < 2500; i++) {
			String[] arr = in.readLine().split(" ");
			int him = arr[0].charAt(0) - 65;
			int you = arr[1].charAt(0) - 88;
			if(you == 0) {
				you = (him + 2) % 3;
			} else {
				if(you == 1) {
					you = him;
				} else {
					you = (him + 1) % 3;
				}
			}
			int diff = you - him;
			if(diff == 0) {
				total += 3;
			}
			if(diff == 1) {
				total += 6;
			}
			if(diff == -2) {
				total += 6;
			}
			total += you + 1;
		}
		System.out.println(total);
	}
}
