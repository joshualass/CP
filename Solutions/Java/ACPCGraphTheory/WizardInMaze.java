import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

public class WizardInMaze {
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
    	int row =in.nextInt();
    	int col = in.nextInt();
    	
    	int startR = in.nextInt()-1;
    	int startC = in.nextInt()-1;
    	
    	int endR = in.nextInt()-1;
    	int endC = in.nextInt()-1;
    	
    	char[][] mat = new char[row][];
    	int[][] map = new int[row][col];
    	for(int i = 0; i < row; i++) {
    		mat[i] = in.nextLine().trim().toCharArray();
    		Arrays.fill(map[i], -1);
    	}
    	for(char[] x : mat) {
    		System.out.println(Arrays.toString(x));
    	}
    	
    	List<int[]> q = new LinkedList<>();
    	q.add(new int[] {startR,startC,0});
    	while(!q.isEmpty()) {
    		int[]arr = q.remove(0);
    		int r = arr[0]; int c = arr[1]; int step = arr[2];
    		//check bounds, and not wall
    		if(r < 0 || r >= row || c < 0 || c >= col || mat[r][c] == '#') {
    			continue;
    		}
    		//check if unvisited or better than previously visited
    		if(map[r][c] == -1 || map[r][c] > step) {
    			map[r][c] = step;
    			q.add(new int[] {r-1,c,step});
    			q.add(new int[] {r+1,c,step});
    			q.add(new int[] {r,c-1,step});
    			q.add(new int[] {r,c+1,step});
    			//add other 20 moves
    			if((r != 0 && mat[r-1][c] == '#') || (r != mat.length-1 && mat[r+1][c] == '#') || (c != 0 && mat[r][c-1] == '#') || (c != mat[0].length-1 && mat[r][c+1] == '#')) {
    				for(int rr = -2; rr <= 2; rr++) {
    					for(int cc = -2; cc <= 2; cc++) {
    					
//    					int[] send = new int[] {r+rr,c+cc,step+1};
//    					if(!(rr == -1 && cc == 0 || rr == 1 && cc == 0 || rr == -0 && cc == -1 || rr == 0 && cc == 1)) {
//    						send[2]--;
//    					}
    						q.add(new int[] {r+rr,c+cc,step+1});
    					}
    				}
    			}

    		}
    	}
    	System.out.println(map[endR][endC]);
	}
}
