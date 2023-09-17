import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class GoodSequence {
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		
		int N = in.nextInt();
		in.nextLine();
		Map<Integer, Integer> map = new HashMap<>();
		
		String[] arr = in.nextLine().split(" ");
		for(int i = 0; i < arr.length; i++) {
			int hold = Integer.parseInt(arr[i]);
			if(map.containsKey(hold)) {
				map.put(hold, map.get(hold) + 1);
			} else {
				map.put(hold, 1);
			}
		}
		int total = 0;
		for (Map.Entry<Integer, Integer> entry : map.entrySet())
		{
//			System.out.println("value" + entry.getValue() + "key " + entry.getKey());
			if(entry.getValue() >= entry.getKey()) {
				total += entry.getValue() - entry.getKey();
			} else {
				total += entry.getValue();
			}
		}
		System.out.println(total);
	}
}
