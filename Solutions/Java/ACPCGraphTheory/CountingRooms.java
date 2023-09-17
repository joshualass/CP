import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

public class CountingRooms {
	
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
		int row = in.nextInt();
		int col = in.nextInt();
//		in.nextLine();
		char[][] mat = new char[row][];
		
		for(int i = 0; i < row; i++) {	
			mat[i] = in.nextLine().trim().toCharArray();
		}
		for(char[] x : mat) {
//			System.out.println(Arrays.toString(x));
		}
		
		int num_comps = 0;
		
		for(int r = 0; r < row; r++) {
			for(int c = 0; c < col; c++) {
				if(mat[r][c] == '.') {
					num_comps++;
					//flood fill
					List<int[]> q = new LinkedList<>();
					q.add(new int[] {r,c});
					while(!q.isEmpty()) {
						int[]  arr = q.remove(0);
						int holdr = arr[0];
						int holdc = arr[1];
						if(holdr == -1 || holdr == row || holdc == -1 || holdc == col || mat[holdr][holdc] == '#') {
							continue;
						}
						mat[holdr][holdc] = '#';
						q.add(new int[] {holdr,holdc-1});
						q.add(new int[] {holdr,holdc+1});
						q.add(new int[] {holdr-1,holdc});
						q.add(new int[] {holdr+1,holdc});
					}
				}
				
				
			}
		}
		System.out.println(num_comps);
	}
}
