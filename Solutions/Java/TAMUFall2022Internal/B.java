import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
 
public class Bell {
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
    	int N = in.nextInt();
    	int M = in.nextInt();
    	ArrayList<String> arr = new ArrayList<>();
    	
    	for(int i = 0; i < N; i++) {
    		arr.add(in.next());
    	}
    	String out = "";
    	for(int i = 0; i < M; i++) {
    		int L = in.nextInt();
    		for(int l = 0; l < L; l++) {
    			String remove = in.next();
    			out += remove + " ";
    			arr.remove(remove);
    		}
    		
    	}
    	for(String x : arr) {
    		out += x + " ";
    	}
    	System.out.println(out);
	}
}