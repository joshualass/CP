import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Solution {
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] arr = in.readLine().split(" ");
		int total = Integer.parseInt(arr[0]);
		int N = Integer.parseInt(arr[1]);
		
		int [] arr1 = new int[N];
		for(int i = 0; i < N; i++) {
			arr1[i] = Integer.parseInt(in.readLine());
		}
		int[]arr2 = new int[N];
		while(total > 0) {
			boolean flag = true;
			for(int i = 0; i < N && total > 0; i++) {
				if(arr1[i] != 0) {
					arr1[i] -= 1;
					arr2[i] += 1;
					total--;
					flag = false;
				}
			}
			if(flag) {
				break;
			}
		}
		for(int i = 0; i < N; i++) {
			System.out.println(arr2[i]);
		}
	}
}
