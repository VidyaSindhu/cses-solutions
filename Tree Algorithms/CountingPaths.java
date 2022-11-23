import java.util.*;
import java.io.*;

public class CountingPaths {
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
    static int l, time;
    static int[] tin, tout;
    static int[][] parent;

    static void build(int node, int p, List<Integer>[] adj){
        tin[node] = ++time;
        parent[node][0] = p;
        for(int i = 1; i <= l; i++){
            if(parent[node][i-1] != -1){
                parent[node][i] = parent[parent[node][i-1]][i-1];
            }
            else{
                parent[node][i] = -1;
            }
        }
        for(int child: adj[node]){
            if(child != p){
                build(child, node, adj);
            }
        }
        tout[node] = ++time;
    }
    
    static boolean isAncestor(int u, int v){
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
    
    static int getLCA(int u, int v){
        if(isAncestor(u, v)) return u;
        else if(isAncestor(v, u)) return v;
        
        for(int i = l-1; i >= 0; i--){
            if(parent[u][i] != -1 && !isAncestor(parent[u][i], v)){
                u = parent[u][i];
            }
        }
        
        return parent[u][0];
    }
    
    public static void main(String[] args) throws IOException{
        // PrintWriter out=new PrintWriter(System.out);
        FastReader in = new FastReader();
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        int n = in.nextInt();
        int m = in.nextInt();
        
        tout = new int[n];
        tin = new int[n];
        
        time = 0;
        l = 19;
        parent = new int[n][l+1];

        List<Integer>[] adj = new ArrayList[n];
        for(int i = 0; i < n; i++){
            adj[i] = new ArrayList<>();
        }
        int u;
        int v;
        for(int i = 0; i < n-1; i++){
            u = in.nextInt();
            v = in.nextInt();
            v--;
            u--;
            adj[u].add(v);
            adj[v].add(u);
        }
        build(0, -1, adj);
        
        int[] value = new int[n];        
        for(int i = 0; i < m; i++){
            int a = in.nextInt()-1;
            int b = in.nextInt()-1;

            int x = getLCA(a, b);
            int p = parent[x][0];
            value[a]++;
            value[b]++;
            value[x]--;
            if(p != -1) value[p]--;
        }

        dfs(0, 0, adj, value);
        StringBuffer sb = new StringBuffer();
        for(int i = 0; i < n; i++){
            out.write(value[i] + " ");
        }
        out.flush();
        out.close();
    }
    
    static void dfs(int node, int p, List<Integer>[] adj, int[] value){
        int x = value[node];
        
        for(int child: adj[node]){
            if(child != p){
                dfs(child, node, adj, value);
                x += value[child];
            }
        }
        value[node] = x;
    }
}
