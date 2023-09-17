import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.StringTokenizer;
 
public class Dank {
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
    	int N = in.nextInt(); //size of garden
    	int M = in.nextInt(); //number of sprinklers
    	
    	Map<Integer,int[]> map = new HashMap<>();
    	
    	for(int i = 0; i < M; i++) {
    		int x = in.nextInt()-1;
    		int r = in.nextInt();
    		String type = in.next();
    		int index = 0;
    		if(type.equals("murky")) {
    			index = 1;
    		}
    		int lower = x - r;
    		if(lower < 0) {
    			lower = 0;
    		}
    		int higher = x + r + 1;
    		if(higher > N-1) {
    			higher = N;
    		}
    		if(map.containsKey(lower)) {
    			int[] arr = map.get(lower);
    			arr[index] += 1;
    			map.put(lower, arr);
    		} else {
    			int[] arr = new int[2];
    			arr[index] = 1;
    			map.put(lower, arr);
    		}
    		if(map.containsKey(higher)) {
    			int[] arr = map.get(higher);
    			arr[index] -= 1;
    			map.put(higher, arr);
    		} else {
    			int[]arr = new int[2];
    			arr[index] = -1;
    			map.put(higher, arr);
    		}
    	}
    	
    	//Iterator hmIterator = map.entrySet().iterator();
    	ArrayList<int[]> list = new ArrayList<>();
    	
    	for (Map.Entry<Integer, int[]> entry : map.entrySet()) {
    		
    		list.add(new int[] {entry.getKey(),entry.getValue()[0],entry.getValue()[1]});
    		
    	}
    	list.sort((x,y) -> x[0] - y[0]);
    	for(int[] x : list) {
//    		System.out.println(Arrays.toString(x));
    	}
    	int d = 0;
    	int m = 0;
    	int prev = 0;
    	int count = 0;
    	for(int i = 0; i < list.size(); i++) {
    		int [] arr = list.get(i);
    		if(d == m && m >= 2 && d >= 2) {
    			count += arr[0] - prev;
    		}
    		d += arr[1];
    		m += arr[2];
    		prev = arr[0];
    		
    		
    	}
    	System.out.println(count);
	}
}