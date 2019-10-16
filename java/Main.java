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
class Unnamed {
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
        ArrayList<ArrayList<Integer>> G;
        long f[];
        long tree[];
        long x[];
        final int mod = (int)(1e9 + 7);
        int n, q, k;
        long ans;
        Matrix mat;
        long tr[];
        int st[];
        int en[];
        int tim = 0;
        int lvl[];
        int par[];
        int table[][];
        int lg[];

        long F(int u) {
            if (f[u] != -1) return f[u];
            long f1 = (F(u - 1) * k) % mod;
            long f3 = (F(u - 3) * (k - 2)) % mod;
            return f[u] = (f1 + f3) % mod;
        }
        
        void dfs( int fr, int u, int dep ) {
            lvl[u] = dep;
            par[u] = fr;
            st[u] = ++tim;
            for( int v: G.get(u) ) {
                if( fr == v ) continue;
                dfs( u, v, dep+1 );
            }
            en[u] = ++tim;
        }

        void init( int n ) {
            for (int[] row: table) {
                Arrays.fill(row, -1);
            }
            for( int i=0; i<n; i++ ) {
                table[i][0] = par[i];
            }
            for( int j=1; ( 1 << j ) < n; j++ ) {
                for( int i=0; i<n; i++ ) {
                    if( table[i][j-1] == -1 ) continue;
                    table[i][j] = table[ table[i][j-1] ][j-1];
                }
            }
            for( int i=0; i<17; i++ ) lg[1 << i] = i;
            for( int i=1; i<sz; i++ ) if( lg[i] == 0 ) lg[i] = lg[i-1];
        }

        int query( int n, int p, int q ) {
            int log;
            if( lvl[p] < lvl[q] ) {
                p ^= q;
                q ^= p;
                p ^= q;
            }
            log = lg[ lvl[ p ] ];
            for( int i=log; i>=0; i-- ) {
                if( lvl[p] - ( 1 << i ) >= lvl[q] ) {
                    p = table[ p ][ i ];
                }
            }
            if( p == q ) return p;
            for( int i=log; i>=0; i-- ) {
                if( table[ p ][ i ] != -1 && table[ p ][ i ] != table[ q ][ i ] ) {
                    p = table[ p ][ i ];
                    q = table[ q ][ i ];
                }
            }
            return par[p];
        }

        long FxFast(long x) {
            if (x == 1) return 1;
            if (x == 2) return 2;
            if (x == 3) return 5;
            Matrix h = mat.Power(x - 3);
            long ret = 0;
            long a = (long)h.a[0][0] * 5 % mod;
            long b = (long)h.a[0][1] * 2 % mod;
            long c = (long)h.a[0][2] * 1 % mod;
            ret = (ret + a) % mod;
            ret = (ret + b) % mod;
            ret = (ret + c) % mod;
            return ret;
        }

        long find_answer( int n, int p, int q ) {
            int lca = query( n, p, q );
            long a = qu(st[p]);
            long b = qu(st[q]);
            long c = tree[lca];
            long d = (mod - ((2 * qu(st[lca])) % mod));
            long ret = 0;
            ret = (ret + a) % mod;
            ret = (ret + b) % mod;
            ret = (ret + c) % mod;
            ret = (ret + d) % mod;
            return ret;
            // return qu(st[p]) + qu(st[q]) + gn[lca] - 2 * qu(st[lca]);
        }

        void upd(int x, long v) {
            for (; x < sz * 2; x += (x & -x)) {
                tr[x] = (tr[x] + v) % mod;
            }
        }

        long qu(int x) {
            long ret = 0;
            for (; x > 0; x -= (x & -x)) {
                ret = (ret + tr[x]) % mod;
            }
            return ret;       
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

            mat = new Matrix(3, mod);
            mat.a[0][0] = k;
            mat.a[0][1] = 0;
            mat.a[0][2] = k - 2;

            mat.a[1][0] = 1;
            mat.a[1][1] = 0;
            mat.a[1][2] = 0;

            mat.a[2][0] = 0;
            mat.a[2][1] = 1;
            mat.a[2][2] = 0;

            tr = new long[sz * 2 + 100];
            x = new long[sz];
            tree = new long[sz];

            lvl = new int[sz];
            par = new int[sz];
            st = new int[sz * 2 + 100];
            en = new int[sz * 2 + 100];
            table = new int[sz][17];
            lg = new int[sz];

            G = new ArrayList<ArrayList<Integer>> ();

            for(int i = 0; i < n; i++) {
                x[i] = in.nextLong();
                G.add(new ArrayList<Integer>());
            }

            int u, v;

            for(int i = 1; i < n; i++) {
                u = in.nextInt();
                v = in.nextInt();
                --u; --v;
                G.get(u).add(v);
                G.get(v).add(u);
            }

            dfs(-1, 0, 0);

            init(n);

            for (int i = 0; i < n; i++) {
                tree[i] = FxFast(x[i]);
                upd(st[i], tree[i]);
                upd(en[i], mod - tree[i]);
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
                    ans = find_answer(n, u, v);
                    out.println(ans);
                } else {
                    u = in.nextInt();
                    x_u = in.nextLong();
                    --u;
                    x[u] = x_u;
                    upd(st[u], mod - tree[u]);
                    upd(en[u], tree[u]);
                    tree[u] = FxFast(x[u]);
                    upd(st[u], tree[u]);
                    upd(en[u], mod - tree[u]);
                }
            }
        }
 
    }
 
    static class  Matrix {
        int matrixSize;
        int mod;
        int[][] a;
        Matrix(int matrixSize, int mod) {
            this.matrixSize = matrixSize;   
            this.mod = mod;
            a = new int[matrixSize][matrixSize];
        }
        void Clear() {
            for (int[] row: a) {
                Arrays.fill(row, 0);
            }
        }
        void Identity() {
            for( int i=0; i<matrixSize; i++ ) {
                for( int j=0; j<matrixSize; j++ ) {
                    a[i][j] = (i == j) ? 1 : 0;
                }
            }
        }
        Matrix Add(Matrix b) {
            Matrix temp = new Matrix(matrixSize, mod);
            temp.Clear();
            for (int i = 0; i <  matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    temp.a[i][j] = a[i][j] + b.a[i][j];
                    if (temp.a[i][j] >= mod) {
                        temp.a[i][j] -= mod;
                    }
                }
            }
            return temp;
        }
        Matrix Multiply(Matrix b) {
            Matrix temp = new Matrix(matrixSize, mod);
            temp.Clear();
            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    for (int k = 0; k < matrixSize; k++) {
                        temp.a[i][k] += (long)a[i][j] * b.a[j][k] % mod;
                        if (temp.a[i][k] >= mod) {
                            temp.a[i][k] -= mod;
                        }
                    }
                }
            }
            return temp;
        }
        Matrix Power(long x) {
            Matrix ans = new Matrix(matrixSize, mod);
            Matrix num = this;
            ans.Identity();
            while (x > 0) {
                if ((x & 1) == 1) {
                    ans = ans.Multiply(num);
                }
                num = num.Multiply(num);
                x >>= 1;
            }
            return ans;
        }
    };

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