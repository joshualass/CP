import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Registration {
	public static void main(String[] args) throws NumberFormatException, IOException {
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(in.readLine());
		Set<String> set = new HashSet<>();
		Map<String, Integer> map = new HashMap<>();
		while(N-->0) {
			String line = in.readLine().trim();
			
			if(!map.containsKey(line)) {
				map.put(line, 0);
				System.out.println("OK");
			} else {
				map.put(line, map.get(line) + 1);
				System.out.println(line + map.get(line));
			}	
//			if(set.add(line)) {
//				System.out.println("OK");
//			} else {
//				int count = 1;
//				while(true) {
//					if(set.add(line + count)) {
//						System.out.println(line + count);
//						break;
//					}
//					count++;
//				}
//			}
		}
	}
}
