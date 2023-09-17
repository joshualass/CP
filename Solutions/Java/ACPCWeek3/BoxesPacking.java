import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class BoxesPacking {
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		
		int N = in.nextInt();
		in.nextLine();
		String[] arr = in.nextLine().split(" ");
		int count = 0;
		Map<String, Integer> map = new HashMap<>();
		for(int i = 0; i < arr.length; i++) {
			String line = arr[i];
			
			if(map.containsKey(line)) {
				map.put(line, map.get(line) + 1);
			} else {
				map.put(line, 1);
			}
		}
		int max = -1;
//		System.out.println(map.values());
		for(int name: map.values()) {
			max = Math.max(name, max);
		}
		System.out.println(max);
	}
}
