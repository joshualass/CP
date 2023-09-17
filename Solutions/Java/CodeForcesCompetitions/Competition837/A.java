package Competition837;

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
			
			int length = in.nextInt();
			
			String[]arr1 = in.nextLine().split(" ");
			int[]arr = new int[length];
			for(int i = 0; i < length; i++) {
				arr[i] = Integer.parseInt(arr1[i]);
			}
			int mincount = 0;
			int maxcount = 0;
			int globalmax = 0;
			int globalmin = 10000000;
			boolean same = true;
			int sameint = arr[0];
			for(int i = 0; i < length; i++) {
				if(sameint != arr[i]) {
					same = false;
				}
				int c = arr[i];
				if(c < globalmin) {
					globalmin = c;
					mincount = 0;
				}
				if(c == globalmin) {
					mincount++;
				}
				if(c > globalmax) {
					globalmax = c;
					maxcount = 0;
				}
				if(c == globalmax) {
					maxcount++;
				}	
			}
			if(same) {
				System.out.println();
			} else {				
				System.out.println(mincount * maxcount * 2);
			}
			
		}
		
		
	}
}
