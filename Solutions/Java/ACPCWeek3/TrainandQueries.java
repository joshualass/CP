import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class TrainandQueries {
	public static void main(String[] args) throws NumberFormatException, IOException {
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(in.readLine());
		while(N-->0) {
			String line = in.readLine();
			while(line.trim().equals("")) {
				line = in.readLine();
			}
			String[] arr = line.trim().split(" ");
			int stations = Integer.parseInt(arr[0]);
			int tests = Integer.parseInt(arr[1]);
			
			Map<Integer, int[]> map = new HashMap<>();
			arr = in.readLine().trim().split(" ");
			for(int i = 0; i < stations; i++) {
				int hold = Integer.parseInt(arr[i]);
				if(!map.containsKey(hold)) {
					map.put(hold, new int[] {i,i});
				} else {
					int[] swap = map.get(hold);
					swap[1] = i;
					map.put(hold, swap);
				}
			}
			
			for (Map.Entry<Integer, int[]> entry : map.entrySet())
			{
//				System.out.println(entry.getKey() + " " + Arrays.toString(entry.getValue()));
			}
			
			for(int i = 0; i < tests; i++) {
				arr = in.readLine().trim().split(" ");
				int start = Integer.parseInt(arr[0]);
				int end = Integer.parseInt(arr[1]);
				
				if(!map.containsKey(start) || !map.containsKey(end)) {
					System.out.println("NO");
					continue;
				}
//				System.out.println("start" + start + "end " + end);
//				System.out.println("starting index" + Arrays.toString(map.get(start)) + "ending index" + Arrays.toString(map.get(end)));
				System.out.println(map.get(start)[0] < map.get(end)[1] ? "YES" :"NO");
			}
		}
		
	}
}
