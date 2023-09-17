import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Path {
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
	    int xcoord = 0;
	    int ycoord = 0;

	    int minx = 0;
	    int miny = 0;
	    int maxx = 0;
	    int maxy = 0;
	    
	    ArrayList<String> arr = new ArrayList<>();
	    
	    while(in.hasNext()) {
	    	String action = in.next();
	    	arr.add(action);
	        if (action == "down")
	        {
	            ycoord--;
	        }
	        if (action == "up")
	        {
	            ycoord++;
	        }
	        if (action == "left")
	        {
	            xcoord--;
	        }
	        if (action == "right")
	        {
	            xcoord++;
	        }
	        minx = Math.min(minx,xcoord);
	        miny = Math.min(miny,ycoord);
	        maxx = Math.max(maxx,xcoord);
	        maxy = Math.max(maxy,ycoord);
	    }
	    System.out.println(minx + " " + maxx + " " + miny + " " + maxy);
	    
	    int rows = 1 + Math.abs(miny) + maxy;
	    int cols = 1 + Math.abs(minx) + maxx;
	    
	    char[][] mat = new char[rows][cols];
	    
	    for(char[] x : mat) {
	    	Arrays.fill(x, ' ');
	    }
	    
	    xcoord = Math.abs(minx);
	    ycoord = Math.abs(miny);
	    
	    mat[ycoord][xcoord] = 'S';
	    
	    for(int i = 0; i < arr.size(); i++) {

	        if (arr.get(i) == "down")
	        {
	            ycoord--;
	        }
	        if (arr.get(i) == "up")
	        {
	            ycoord++;
	        }
	        if (arr.get(i) == "left")
	        {
	            xcoord--;
	        }
	        if (arr.get(i) == "right")
	        {
	            xcoord++;
	        }
	        if(mat[ycoord][xcoord] == ' ') {
	            mat[ycoord][xcoord] = '*';
	        }
	    }
	    mat[ycoord][xcoord] = 'E';
	    

	    String out = "";
	    for(int i = 0; i < cols + 2; i++) {
	        out += '#';
	    }
	    out += "\n";
	    for(char[] x : mat) {
	        out += '#';
	        for(char y : x) {
	            out += y;
	        }
	        out += "#\n";
	    }
	    for(int i = 0; i < cols + 2; i++) {
	        out += '#';
	    }
	    System.out.println(out);
		
	}
}
