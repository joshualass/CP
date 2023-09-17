import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class KAIBUNsyo {
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
    	LinkedList<Integer>[] arr = new LinkedList[200001];
    	for(int i = 0; i < arr.length; i++) {
    		arr[i] = new LinkedList<>();
    	}
    	String[] nums = in.nextLine().trim().split(" ");
    	
    	for(int i = 0; i <= nums.length/2; i++) {
    		int first = Integer.parseInt(nums[i]);
    		int last = Integer.parseInt(nums[nums.length-1-i]);
    		if(first != last) {
    			arr[first].add(last);
    			arr[last].add(first);
    		}
    	}
    	
    	boolean[]visited = new boolean[200001];
    	int num_comps = 0;
    	int total = 0;
    	for(int i = 0; i < visited.length; i++) {
    		if(!visited[i] && arr[i].size() != 0) {
    			LinkedList<Integer> q = new LinkedList<>();
    			num_comps++;
    			q.add(i);
    			while(!q.isEmpty()) {
    				int x = q.remove();
    				if(!visited[x]) {
    					total++;
    					for(int y : arr[x]) {
    						q.add(y);
    					}
    					visited[x] = true;
    				}
    			}
    		}
    	}
    	System.out.println(total-num_comps);
	}
}
