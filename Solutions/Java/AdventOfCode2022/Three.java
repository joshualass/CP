import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Three {
	public static void main(String[] args) throws IOException {
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		long total = 0;
		for(int t = 0; t < 100; t++) {
			
			String line1 = in.readLine();
			String line2 = in.readLine();
			String line3 = in.readLine();
			boolean[] arr1 = new boolean[200];
			boolean[] arr2 = new boolean[200];
			boolean[] arr3 = new boolean[200];
			for(int i = 0; i < line1.length(); i++) {
				arr1[line1.charAt(i)] = true;
			}
			for(int i = 0; i < line2.length(); i++) {
				arr2[line2.charAt(i)] = true;
			}
			for(int i = 0; i < line3.length(); i++) {
				arr3[line3.charAt(i)] = true;
			}
			for(int i = 0; i < 200; i++) {
				
				if(arr1[i] && arr2[i] && arr3[i]) {
					int val = 0;
					if(i >= 97) {
						val = i - 96;
					} else {
						val = i - 65 + 27;
					}
					total += val;
					break;
				}
				
			}
			
		}
		System.out.println(total);
		
	}
}
