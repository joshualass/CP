import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;
 
public class Cake {
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
    	int N = in.nextInt(); // cuts
    	int K = in.nextInt(); // slices to take
    	double R = in.nextDouble(); // radius of cake
    	
    	ArrayList<Double> arr = new ArrayList<>();
    	for(int i = 0; i < N; i++) {
    		double d = in.nextDouble();
    		arr.add(d);
    		arr.add(d+180);
    	}
    	Collections.sort(arr);
    	int from = 0; 
    	int to = K;
    	double maxA = 0;
    	for(int i = 0; i < arr.size(); i++) {
    		from = i;
    		to = (i + K) % arr.size();
//    		System.out.println("from" + from + "to" + to + maxA);
//    		System.out.println(arr.get(to) + " " + arr.get(from));
    		double ans = arr.get(to) - arr.get(from);
    		if(ans < 0) {
    			ans += 360;
    		}
    		maxA = Math.max(maxA, ans);
    	}
//    	System.out.println(maxA);
    	double math = Math.PI * R * R * maxA / 360;
    	if(N * 2 == K) {
    		math = Math.PI * R * R;
    	}
    	System.out.println(math);
	}
}