#include <bits/stdc++.h>
using namespace std;

const int sz = 1e5 + 10;

using ll = long long;
const int n_lim = 1e5;
const int q_lim = 1e5;
const ll x_lim = 1e18;
const int k_lim = 50;
const ll mod = 1e9 + 7;
int n, q, k;
ll x[sz];

int lg[sz];
int lvl[sz];
int table[sz][17];
int par[sz];
int tim;
int st[sz * 2], en[sz * 2];
ll tr[sz * 2];
vector < int > G[sz];

void dfs( int fr, int u, int dep ) {
    lvl[u] = dep;
    par[u] = fr;
    st[u] = ++tim;
    for( int v: G[u] ) {
        if( fr == v ) continue;
        dfs( u, v, dep+1 );
    }
    en[u] = ++tim;
}

void init( int n ) {
    memset( table, -1, sizeof table );
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
    for( int i=1; i<sz; i++ ) if( !lg[i] ) lg[i] = lg[i-1];
}

int query( int n, int p, int q ) {
    int log;
    if( lvl[p] < lvl[q] ) swap( p, q );
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

void upd(int x, ll v) {
    for (; x < sz * 2; x += (x & -x)) {
        tr[x] = (tr[x] + v) % mod;
    }
}

ll qu(int x) {
    ll ret = 0;
    for (; x > 0; x -= (x & -x)) {
        ret = (ret + tr[x]) % mod;
    }
    return ret;       
}

ll f[sz];
ll tree[sz];

struct Matrix {
    int mat_sz;
    vector < vector < int > > a;
    Matrix(int _mat_sz) :
        mat_sz(_mat_sz),
        a(vector < vector < int > > (_mat_sz, vector < int > (_mat_sz, 0)))
    {}
    void clear() {
        for (int i = 0; i < mat_sz; i++) {
            fill(a[i].begin(), a[i].end(), 0);
        }
    }
    void one() {
        for( int i=0; i<mat_sz; i++ ) {
            for( int j=0; j<mat_sz; j++ ) {
                a[i][j] = i == j;
            }
        }
    }
    Matrix operator + (const Matrix &b) const {
        Matrix tmp(mat_sz);
        tmp.clear();
        for (int i = 0; i <  mat_sz; i++) {
            for (int j = 0; j < mat_sz; j++) {
                tmp.a[i][j] = a[i][j] + b.a[i][j];
                if (tmp.a[i][j] >= mod) {
                    tmp.a[i][j] -= mod;
                }
            }
        }
        return tmp;
    }
    Matrix operator * (const Matrix &b) const {
        Matrix tmp(mat_sz);
        tmp.clear();
        for (int i = 0; i < mat_sz; i++) {
            for (int j = 0; j < mat_sz; j++) {
                for (int k = 0; k < mat_sz; k++) {
                    tmp.a[i][k] += (long long)a[i][j] * b.a[j][k] % mod;
                    if (tmp.a[i][k] >= mod) {
                        tmp.a[i][k] -= mod;
                    }
                }
            }
        }
        return tmp;
    }
    Matrix pw(ll x) {
        Matrix ans(mat_sz), num = *this;
        ans.one();
        while (x > 0) {
            if (x & 1) {
                ans = ans * num;
            }
            num = num * num;
            x >>= 1;
        }
        return ans;
    }
};

ll find_answer( int n, int p, int q ) {
    int lca = query( n, p, q );
    ll a = qu(st[p]);
    ll b = qu(st[q]);
    ll c = tree[lca];
    ll d = (mod - ((2 * qu(st[lca])) % mod));
    ll ret = 0;
    ret = (ret + a) % mod;
    ret = (ret + b) % mod;
    ret = (ret + c) % mod;
    ret = (ret + d) % mod;
    return ret;
    // return qu(st[p]) + qu(st[q]) + gn[lca] - 2 * qu(st[lca]);
}

ll F(int u) {
    if (f[u] != -1) return f[u];
    ll f1 = (F(u - 1) * k) % mod;
    ll f3 = (F(u - 3) * (k - 2)) % mod;
    return f[u] = (f1 + f3) % mod;
}

Matrix mat(3);

ll FxFast(ll x) {
    if (x == 1) return 1;
    if (x == 2) return 2;
    if (x == 3) return 5;
    Matrix h = mat.pw(x - 3);
    ll ret = 0;
    ll a = (1ll * h.a[0][0] * 5) % mod;
    ll b = (1ll * h.a[0][1] * 2) % mod;
    ll c = (1ll * h.a[0][2] * 1) % mod;
    ret = (ret + a) % mod;
    ret = (ret + b) % mod;
    ret = (ret + c) % mod;
    return ret;
}

int main() {

    memset(f, -1, sizeof f);

    f[1] = 1;

    f[2] = 2;

    f[3] = 5;

    scanf("%d %d %d", &n, &q, &k);

    assert(1 <= n && n <= n_lim);

    assert(1 <= q && q <= q_lim);

    assert(2 <= k && k <= k_lim);

    mat.a[0][0] = k;
    mat.a[0][1] = 0;
    mat.a[0][2] = k - 2;

    mat.a[1][0] = 1;
    mat.a[1][1] = 0;
    mat.a[1][2] = 0;

    mat.a[2][0] = 0;
    mat.a[2][1] = 1;
    mat.a[2][2] = 0;

    for(int i = 0; i < n; i++) {
        scanf("%lld", &x[i]);
        assert(1ll <= x[i] && x[i] <= x_lim);
    }

    for(int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        assert(u != v);
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(-1, 0, 0);

    init(n);

    memset(tr, 0, sizeof tr);

    for (int i = 0; i < n; i++) {
        tree[i] = FxFast(x[i]);
        upd(st[i], tree[i]);
        upd(en[i], mod - tree[i]);
    }

    while(q--) {
        int type, u, v;
        ll x_u;
        scanf("%d", &type);
        assert(1 <= type && type <= 2);
        if (type == 1) {
            scanf("%d %d", &u, &v);
            --u, --v;
            assert(0 <= u && u < n);
            assert(0 <= v && v < n);
            printf("%lld\n", find_answer(n, u, v));
        } else {
            scanf("%d %lld", &u, &x_u);
            --u;
            x[u] = x_u;
            assert(0 <= u && u < n);
            assert(1ll <= x[u] && x[u] <= x_lim);
            upd(st[u], mod - tree[u]);
            upd(en[u], tree[u]);
            tree[u] = FxFast(x[u]);
            upd(st[u], tree[u]);
            upd(en[u], mod - tree[u]);
        }
    }

    return 0;
}