import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;

public class One {
	
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
	
	public static void main(String[] args) throws IOException {
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		long max = -1;
		long localmax = 0;
		
		Queue<Long> q = new PriorityQueue<>();
		for(int i = 0; i < 2244; i++) {
			String line = in.readLine();
			if(line.equals("")) {
				if(q.size() != 3) {
					q.add(localmax);
				} else {
					if(localmax > q.peek()) {
						q.poll();
						q.add(localmax);
					}
				}
				localmax = 0;
			} else {				
				localmax += Integer.parseInt(line);
			}
			
			
		}
		
		long total = 0;
		for ( long x : q) {
			total += x;
		}
		
		System.out.println(total);
		
	}
}
