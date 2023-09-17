import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class wordladder3 {
	public static void main(String[] args) throws NumberFormatException, IOException {
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String s = "aaaaaaaaaa";
		int ticker = 0;
		
		int N = Integer.parseInt(in.readLine());
		for(int i = 0; i < N; i++) {
			
			System.out.println(s);
			if(i % 2 == 0) {
				s = s.substring(0,ticker) + (char)(s.charAt(ticker)+1) + s.substring(ticker+1,10);
			} else {
				
				if(s.charAt(ticker) == 97) {
					s = s.substring(0,ticker) + 'z' + s.substring(ticker+1,10);
				} else {
					s = s.substring(0,ticker) + (char)(s.charAt(ticker)-1) + s.substring(ticker+1,10);
				}
			}
			
			ticker = (ticker + 1) % 10;
			
		}
		
	}
}
