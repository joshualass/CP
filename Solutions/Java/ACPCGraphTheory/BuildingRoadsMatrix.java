import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.StringTokenizer;

public class BuildingRoadsMatrix {
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
    	
        int n = in.nextInt();
        int m = in.nextInt();
        
        int[][] arr = new int[n][100001];
        for(int i = 0; i < arr.length; i++) {
        	Arrays.fill(arr[i], -1);
        }
        for(int i = 0; i < m; i++) {
//        	in.nextLine();
        	int u = in.nextInt()-1;
        	int v = in.nextInt()-1;
        	for(int uv = 0; uv < 100001; uv++) {
        		if(arr[u][uv] == -1) {
        			arr[u][uv] = v;
        			break;
        		}
        	}
        	for(int vu = 0; vu < 100001; vu++) {
        		if(arr[v][vu] == -1) {
        			arr[v][vu] = u;
        			break;
        		}
        	}
        }
        int number_components = 0;
        boolean[] visited = new boolean[n];
        
        ArrayList<Integer> leaders = new ArrayList<>();
        for(int v = 0; v < n; v++) {
        	if(!visited[v]) {
        		number_components++;
        		Deque<Integer> q = new ArrayDeque<>();
        		visited[v] = true;
        		q.add(v);
//        		System.out.println("v" + v);
        		while(q.size() != 0) {
        			int node = q.poll();
        			for(Integer x : arr[node]) {
        				if(x == -1) {
        					break;
        				}
        				if(!visited[x]) {
            				q.add(x);
            				visited[x] = true;
//            				System.out.println("x" + x);
        				}
        			}
        		}
        		leaders.add(v);	
        	}
        }
    	System.out.println(number_components-1);
    	for(int i = 0; i < leaders.size()-1; i++) {
    		System.out.println((leaders.get(i)+1) + " " + (leaders.get(i+1)+1));
    		
    	}
    	
        
        
	}
}
