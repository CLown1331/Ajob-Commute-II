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
ll f[sz];
ll tree[sz];
ll ans;

vector <int> G[sz];

ll F(int u) {
    if (f[u] != -1) return f[u];
    ll f1 = (F(u - 1) * k) % mod;
    ll f3 = (F(u - 3) * (k - 2)) % mod;
    return f[u] = (f1 + f3) % mod;
}

void dfs(int u, int pr, ll sum, int d) {
    if (u == d) {
        ans = sum;
        return;
    }
    for (const int& v: G[u]) {
        if (v != pr) {
            dfs(v, u, (sum + tree[v]) % mod, d);
        }
    }
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

    for(int i = 0; i < n; i++) {
        scanf("%lld", &x[i]);
        assert(1ll <= x[i] && x[i] <= x_lim);
        tree[i] = F(x[i]);
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
            dfs(u, -1, tree[u] % mod, v);
            printf("%lld\n", ans);
        } else {
            scanf("%d %lld", &u, &x_u);
            --u;
            x[u] = x_u;
            assert(0 <= u && u < n);
            assert(1ll <= x[u] && x[u] <= x_lim);
            tree[u] = F(x[u]);
        }
    }

    return 0;
}