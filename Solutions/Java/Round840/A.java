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
			int[]arr = new int[L];
			boolean[] zeroes = new boolean[12];
			boolean[] ones = new boolean[12];
			int globmax = 0;
			int globmin = 2000;
			for(int i = 0; i < L ;i++) {
				arr[i] = in.nextInt();
				int num = arr[i];
				globmax = Math.max(globmax, num);
				globmin = Math.min(globmin, num);
				for(int t = 0; t < 12; t++) {
					if(num % 2 == 0) {
						zeroes[t] = true;
					} else {
						ones[t] = true;
					}
					num /= 2;
				}
				
			}
			for(int l = 0; l < L; l++) {
				
				boolean[] temp = new boolean[12];
				int num = arr[l];
				for(int t = 0; t < 12; t++) {
					if(num % 2 == 1) {
						temp[t] = true;
					}
					num /= 2;
				}
				for(int t = 11; t >= 0; t--) {
					if(ones[t] && !temp[t]) {
						temp[t] = true;
					}
				}
				int num2 = arr[l];
				boolean[]temp2 = new boolean[12];
				for(int t = 0; t < 12; t++) {
					if(num2 % 2 == 1) {
						temp2[t] = true;
					}
					num2 /= 2;
				}
				for(int t = 11; t >= 0; t--) {
					if(temp2[t] && zeroes[t]) {
						temp2[t] = false;
					}
				}
				for(int i = 0; i < 12; i++) {
					if(temp[i]) {
						num += (int)Math.pow(2, i);
					}
					if(temp2[i]) {
						num2 += (int)Math.pow(2, i);
					}
				}
				
				globmax = Math.max(globmax, num);
				globmin = Math.min(globmin, num2);
			}
			System.out.println(globmax-globmin);
		}
		
	}
}
