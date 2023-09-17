import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringTokenizer;

public class B {
	
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
  
        public FastReader()
        {
            br = new BufferedReader(
                new InputStreamReader(System.in));
        }
  
        String next()
        {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                }
                catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
  
        int nextInt() { return Integer.parseInt(next()); }
  
        long nextLong() { return Long.parseLong(next()); }
  
        double nextDouble()
        {
            return Double.parseDouble(next());
        }
  
        String nextLine()
        {
            String str = "";
            try {
                if(st.hasMoreTokens()){
                    str = st.nextToken("\n");
                }
                else{
                    str = br.readLine();
                }
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
	
	public static void main(String[] args) {
		
		FastReader in = new FastReader();
		
		int T = in.nextInt();
		while(T-->0) {
			int N = in.nextInt();
			int K = in.nextInt();
			int[] H = new int[N];
			int[] P = new int[N];
			for(int i = 0; i < N; i++) {
				H[i] = in.nextInt();
			}
			for(int i = 0; i < N; i++) {
				P[i] = in.nextInt();
			}
			ArrayList<int[]> arr = new ArrayList<>();
			ArrayList<Integer> arr2 = new ArrayList<>();
			for(int i = 0; i < N; i++) {
				arr.add(new int[] {H[i],P[i]});
				arr2.add(P[i]);
			}
			arr.sort((x,y) -> x[0] - y[0]);
			Collections.sort(arr2);
			int damage = 0;
			int index = 0;
			while(K > 0 && index != arr.size()) {
				damage += K;
				while(index != arr.size() && arr.get(0)[0] <= damage) {
					int pow = arr.get(0)[1];
					int low = 0;
					int high = arr2.size() - 1;
					while(low != high) {
						int mid = (low + high)/2;
						if(pow == arr2.get(mid)) {
							low = mid;
							high = mid;
						} else {							
							if(pow > arr2.get(mid)) {
								low = mid + 1;
							} else {
								high = mid- 1;
							}
						}
					}
					arr2.remove(low);
					index++;
				}
//				System.out.println(arr.size() + " " + arr2.size());
				if(arr2.size() != 0) {					
					K -= arr2.get(0);
				}
			}
			System.out.println(index != arr.size() ? "NO" : "YES");
		}
	}
}
