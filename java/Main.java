import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.util.ArrayList;
import java.io.InputStream;
import java.util.Arrays;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author CLown1331
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        OutputWriter out = new OutputWriter(outputStream);
        Solver solver = new Solver();
        solver.solve(1, in, out);
        out.close();
    }
 
    static class Solver {
        final int sz = (int)(1e5 + 10);
        ArrayList<Integer>[] G;
        long f[];
        long tree[];
        long x[];
        final long mod = (long)(1e9 + 7);
        int n, q, k;
        long ans;

        long F(int u) {
            if (f[u] != -1) return f[u];
            long f1 = (F(u - 1) * k) % mod;
            long f3 = (F(u - 3) * (k - 2)) % mod;
            return f[u] = (f1 + f3) % mod;
        }
        
        void dfs(int u, int pr, long sum, int d) {
            if (u == d) {
                ans = sum;
                return;
            }
            for (int v: G[u]) {
                if (v != pr) {
                    dfs(v, u, (sum + tree[v]) % mod, d);
                }
            }
        }

        public void solve(int testNumber, InputReader in, OutputWriter out) {
            f = new long[sz];
            Arrays.fill(f, -1);
            f[1] = 1;
            f[2] = 2;
            f[3] = 5;
            n = in.nextInt();
            q = in.nextInt();
            k = in.nextInt();
            x = new long[n];
            tree = new long[n];
            G = (ArrayList<Integer>[])(new ArrayList[n]);
            for(int i = 0; i < n; i++) {
                x[i] = in.nextLong();
                tree[i] = F((int)x[i]);
                G[i] = new ArrayList<Integer>();
            }
            int u, v;
            for(int i = 1; i < n; i++) {
                u = in.nextInt();
                v = in.nextInt();
                --u; --v;
                G[u].add(v);
                G[v].add(u);
            }

            int type;
            long x_u;

            while(q > 0) {
                q--;
                type = in.nextInt();
                if (type == 1) {
                    u = in.nextInt();
                    v = in.nextInt();
                    --u; --v;
                    dfs(u, -1, tree[u] % mod, v);
                    out.println(ans);
                } else {
                    u = in.nextInt();
                    x_u = in.nextLong();
                    --u;
                    x[u] = x_u;
                    tree[u] = F((int)x[u]);
                }
            }
        }
 
    }
 
    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;
 
        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }
 
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }
 
        public int nextInt() {
            return Integer.parseInt(next());
        }
 
        public long nextLong() {
            return Long.parseLong(next());
        }
    }
 
    static class OutputWriter {
        private final PrintWriter writer;
 
        public OutputWriter(OutputStream outputStream) {
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
        }
 
        public OutputWriter(Writer writer) {
            this.writer = new PrintWriter(writer);
        }
 
        public void close() {
            writer.close();
        }
 
        public void println(long i) {
            writer.println(i);
        }
 
    }
}