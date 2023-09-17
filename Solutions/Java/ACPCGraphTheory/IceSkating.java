import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

public class IceSkating {
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
		int[][] mat = new int[N][2];
		boolean[][] map = new boolean[1000][1000];
		List<Integer>[] arrx = new LinkedList[1000];
		List<Integer>[] arry = new LinkedList[1000];
		for(int i = 0; i < 1000; i++) {
			arrx[i] = new LinkedList<>();
			arry[i] = new LinkedList<>();
		}
		for(int i = 0; i < N; i++) {
			int x= in.nextInt()-1;
			int y = in.nextInt()-1;
			mat[i][0] = x;
			mat[i][1] = y;
			map[x][y] = true;
			arrx[x].add(y);
			arry[y].add(x);
		}
		int number_components = 0;
		for(int i = 0; i < N; i++) {
			if(map[mat[i][0]][mat[i][1]]) {
				number_components++;
				List<int[]> q = new LinkedList<>();
				q.add(new int[] {mat[i][0],mat[i][1]});
				while(!q.isEmpty()) {
					int[]arr = q.remove(0);
					if(map[arr[0]][arr[1]]) {
						map[arr[0]][arr[1]] = false;
						for(int y : arrx[arr[0]]) {
							q.add(new int[] {arr[0],y});
						}
						for(int x : arry[arr[1]]) {
							q.add(new int[] {x,arr[1]});
						}
					}
				}
				
			}
		}
		System.out.println(number_components-1);
	}
}
