import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;
 
public class Trails {
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
    	
    	Stack<Integer> stack = new Stack<>();
    	for(int i = 0; i < N; i++) {
    		int next = in.nextInt();
    		if(!stack.isEmpty()) {
    			if(stack.peek() == next) {
    				stack.pop();
    			} else {
    				stack.push(next);
    			}
    		} else {
    			stack.push(next);
    		}
    	}
    	
    	System.out.println(stack.isEmpty() ? "YES" : "NO");
	}
}