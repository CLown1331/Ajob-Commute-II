#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using edge = pair <int, int>;

const int sz = 1e5 + 10;

vector <edge> edges;

int parent[sz];
int count_tree[sz];

void make_dsu() {
    for(int i = 0; i < sz; i++) {
        parent[i] = i;
        count_tree[i] = 1;
    }
}

int find_parent(int x) {
    return (parent[x] == x) ? parent[x] : find_parent(parent[x]);
}

void unite(int x, int y) {
    x = find_parent(x);
    y = find_parent(y);
    if (x != y) {
        count_tree[y] += count_tree[x];
        parent[x] = parent[y];
    }
}

// exe, filename, seed, n_limit, q_limit, k_limit, x_limit
int main(int argc, char** argv) {

    if (argc != 7) {
        fprintf(stderr, "must provide filename, seed, n_limit, q_limit, k_limit, x_limit");
        assert(false);
    }

    char* filename = argv[1];

    int seed = atoi(argv[2]);

    int n_limit = atoi(argv[3]);

    int q_limit = atoi(argv[4]);

    int k_limit = atoi(argv[5]);

    ll x_limit = atoll(argv[6]);

    FILE *file = fopen(filename, "w+");

    mt19937_64 rng(seed);

    int n = n_limit;

    int q = q_limit;

    int k = 2 + (rng() % (k_limit - 1));

    assert(1 <= n && n <= n_limit);

    assert(1 <= q && q <= q_limit);

    assert(2 <= k && k <= k_limit);

    fprintf(file, "%d %d %d\n", n, q, k);

    for (int i = 1; i <= n; i++) {
        ll x_i = 1ll + (rng() % x_limit);
        assert(1 <= x_i && x_i <= x_limit);
        fprintf(file, "%lld%c", x_i, " \n"[i == n]);
    }  

    int u, v;

    make_dsu();

    for (int i = 1; i < n; i++) {
        u = i + 1;
        v = (rng() % i) + 1;
        edges.push_back(make_pair(u, v));
        unite(u, v);
    }

    shuffle(edges.begin(), edges.end(), rng);

    assert(count_tree[find_parent(1)] == n);

    for (const edge &e: edges) {
        fprintf(file, "%d %d\n", e.first, e.second);
    }

    ll x;

    for (int i = 1; i <= q; i++) {
        int type = (rng() % 2) + 1;
        fprintf(file, "%d ", type);
        if (type == 1) {
            u = (rng() % n) + 1;
            while ((v = (rng() % n) + 1) == u);
            fprintf(file, "%d %d\n", u, v);
        } else {
            u = (rng() % n) + 1;
            x = (rng() % x_limit) + 1;
            assert(1 <= u && u <= n);
            assert(1 <= x && x <= x_limit);
            fprintf(file, "%d %lld\n", u, x);
        }
    }

    fclose(file);

    return 0;
}