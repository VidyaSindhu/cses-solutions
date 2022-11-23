import java.util.*;
import java.io.*;

public class SubtreeQueries{
    static int time = 1;
    static int[] start;
    static int[] end;
    static ArrayList<Integer>[] adj;
    static long[] lt;
    static int[] value;

    static long[] BIT;

    static void update(int x, long delta){
        ++x;
        while(x < BIT.length){
            BIT[x] += delta;
            x += (-x & x);
        }
    }

    static long querySum(int x){
        long sum = 0;
        ++x;
        while(x > 0){
            sum += BIT[x];
            x -= (-x & x);
        }
        return sum;
    }
    
    static class FastReader{
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st=new StringTokenizer("");
		String next() {
			while (!st.hasMoreTokens())
				try { 
                                        st=new StringTokenizer(br.readLine());				               
                                } catch (IOException e) {}
			return st.nextToken();
		}
		
		int nextInt() {
			return Integer.parseInt(next());
		}
		long nextLong() {
			return Long.parseLong(next());
		}
    }
    public static void main(String[] args) {
        PrintWriter out=new PrintWriter(System.out);
        FastReader in = new FastReader();
        
        int n = in.nextInt();
        int q = in.nextInt();
        value = new int[n+1];
        for(int i = 1; i < n+1; i++){
            value[i] = in.nextInt();
        }

        start = new int[n+1];
        end = new int[n+1];
        lt = new long[2 * n + 5];
        BIT = new long[lt.length];
        
        
        adj = new ArrayList[n+1];
        for(int i = 0; i < n+1; i++){
            adj[i] = new ArrayList<>();
        }
        int u;
        int v;
        for(int i = 1; i < n; i++){
            u = in.nextInt();
            v = in.nextInt();
            adj[u].add(v);
            adj[v].add(u);
        }
        dfs(1, -1);
        
        for(int i = 1; i < time; i++){
            update(i, lt[i]);
        }

        while(q --> 0){
            int op = in.nextInt();
            int node = in.nextInt();
            if(op == 1){
                int val = in.nextInt();
                long delta = val - value[node];
                update(start[node], delta);
                update(end[node], delta);
                value[node] = val;
            }
            else if(op == 2){
                long ans = querySum(end[node]) - querySum(start[node]-1);
                ans = ans/2;
                out.println(ans);
            }
        }
        out.close();
    }

    static void dfs(int node, int p){
        start[node] = time;
        lt[time++] = value[node];

        for(int child : adj[node]){
            if(child != p){
                dfs(child, node);
            }
        }

        end[node] = time;
        lt[time++] = value[node];
    }
}

