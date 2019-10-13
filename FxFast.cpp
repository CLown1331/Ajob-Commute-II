#include <bits/stdc++.h>
using namespace std;

const int sz = 1e5 + 10;

using ll = long long;
const int n_lim = 1e5;
const int q_lim = 1e5;
const ll x_lim = 1e18;
const int k_lim = 50;
const ll mod = 1e9 + 7;
int k;
ll f[sz];

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


ll F(int u) {
    if (f[u] != -1) return f[u];
    ll f1 = (F(u - 1) * k) % mod;
    ll f3 = (F(u - 3) * (k - 2)) % mod;
    return f[u] = (f1 + f3) % mod;
}

int main() {

    memset(f, -1, sizeof f);

    f[1] = 1;

    f[2] = 2;

    f[3] = 5;

    k = 4;

    mat.a[0][0] = k;
    mat.a[0][1] = 0;
    mat.a[0][2] = k - 2;
    // mat.a[0][3] = 0;

    mat.a[1][0] = 1;
    mat.a[1][1] = 0;
    mat.a[1][2] = 0;
    // mat.a[1][3] = 0;

    mat.a[2][0] = 0;
    mat.a[2][1] = 1;
    mat.a[2][2] = 0;
    // mat.a[2][3] = 0;

    // mat.a[3][0] = 0;
    // mat.a[3][1] = 0;
    // mat.a[3][2] = 1;
    // mat.a[3][3] = 0;

    cout << F(1) << "\n";
    cout << F(2) << "\n";
    cout << F(3) << "\n";
    cout << F(4) << "\n";
    cout << F(5) << "\n";
    cout << F(30) << "\n";
    cout << F(46) << "\n";
    cout << F(340) << "\n";

    cout << FxFast(1) << "\n";
    cout << FxFast(2) << "\n";
    cout << FxFast(3) << "\n";
    cout << FxFast(4) << "\n";
    cout << FxFast(5) << "\n";
    cout << FxFast(30) << "\n";
    cout << FxFast(46) << "\n";
    cout << FxFast(340) << "\n";

    assert(F(1) == FxFast(1));
    assert(F(2) == FxFast(2));
    assert(F(3) == FxFast(3));
    assert(F(4) == FxFast(4));
    assert(F(5) == FxFast(5));
    assert(F(30) == FxFast(30));
    assert(F(46) == FxFast(46));
    assert(F(340) == FxFast(340));

    return 0;
}