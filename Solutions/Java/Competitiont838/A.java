import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


    
public class A {
	
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
		while(N-->0) {
			
			int L = in.nextInt();
			int sum = 0;
			int minops = 100000000;
			for(int i = 0; i < L; i++) {
				int hold = in.nextInt();
				sum += hold;
				int total = 0;
				int temp = hold + 0;
				while((hold + temp) % 2 == 0) {
					hold /= 2;
					total++;
				}
				minops = Math.min(minops, total);
			}
			if(sum % 2 == 0) {
				System.out.println(0);
			} else {
				System.out.println(minops);
			}
		}
		
	}
}
