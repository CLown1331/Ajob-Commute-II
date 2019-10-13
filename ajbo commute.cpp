#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int sz = 1e5 + 10;

using ll = long long;

int n, qry;

int lg[sz];
int lvl[sz];
ll dis[sz];
int table[sz][17];
int gcd[sz][17];
int par[sz];

vector < pair < int, int > > G[sz];

void dfs( int fr = -1, int u = 0, int dep = 0, ll di = 0, int w = 0 ) {
        lvl[u] = dep;
        par[u] = fr;
        dis[u] = di;
        gcd[u][0] = w;
        for( const auto &vv: G[u] ) {
                if( fr == vv.first ) continue;
                dfs( u, vv.first, dep + 1, di + vv.second, vv.second );
        }
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
                        gcd[i][j] = __gcd( gcd[ table[i][j-1] ][j - 1], gcd[i][j - 1] );
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

int dist( int n, int p, int q ) {
        int lca = query( n, p, q );
        return lvl[p] + lvl[q] - 2 * lvl[lca];
}

int get_gcd( int n, int lca, int p ) {
        if( lca == p ) return 0;
        int ret = 0;
        int log = lg[ lvl[ p ] ];
        for( int i=log; i>=0; i-- ) {
                if( lvl[p] - ( 1 << i ) >= lvl[lca] ) {
                        ret = __gcd( ret, gcd[ p ][ i ] );
                        p = table[ p ][ i ];
                }
        }
        return ret;
}

void solve( int n, int p, int q ) {
        int lca = query( n, p, q );
        ll ans = dis[p] + dis[q] - dis[lca] - dis[lca];
        int coin = __gcd( get_gcd( n, lca, p ), get_gcd( n, lca, q ) );
        assert( coin > 0 );
        assert( ans > 0 );
        printf( "%d %lld\n", coin, ans / coin );
}

int main() {

        scanf( "%d %d", &n, &qry );

        int x, y, w;

        for( int i=1; i<n; i++ ) {
                scanf( "%d %d %d", &x, &y, &w );
                --x, --y;
                assert( x != y );
                assert( 0 <= x && x < n );
                assert( 0 <= y && y < n );
                assert( 0 < w && w <= 1000000 );
                G[ x ].push_back( make_pair( y, w ) );
                G[ y ].push_back( make_pair( x, w ) );
        }

        dfs();

        init( n );

        while( qry-- ) {
                scanf( "%d %d", &x, &y );
                --x, --y;
                assert( x != y );
                assert( 0 <= x && x < n );
                assert( 0 <= y && y < n );
                solve( n, x, y );
        }

        return 0;
}