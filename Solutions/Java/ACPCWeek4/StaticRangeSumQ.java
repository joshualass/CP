import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class StaticRangeSumQ {
	public static void main(String[] args) throws IOException {
		
		FastReader fr = new FastReader();
		String line = fr.nextLine();
		int length = Integer.parseInt(line.split(" ")[0]);
		int queers = Integer.parseInt(line.split(" ")[1]);
		
		String[]hold = fr.nextLine().trim().split(" ");
		int[] arr = new int[length];
		for(int i = 0; i < length; i++) {
			if(i == 0) {
				arr[i] = Integer.parseInt(hold[i]);
			} else {
				arr[i] = arr[i-1] + Integer.parseInt(hold[i]);
			}
		}
//		System.out.println(Arrays.toString(arr));
		for(int i = 0; i < queers; i++) {
			int beg = fr.nextInt();
			int end = fr.nextInt();
			if(beg == 1) {
				System.out.println(arr[end-1]);
			} else {
				System.out.println(arr[end-1] - arr[beg-2]);
			}
		}
	}
	
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
}
