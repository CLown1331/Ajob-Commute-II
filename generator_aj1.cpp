#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <algorithm>
using namespace std;

unsigned get_rand() {
        return rand() * rand();
}

const int sz = 1e5 + 10;

int par[sz];
int cnt[sz];

struct edge {
        int x, y, w;
        edge() {}
        edge( int a, int b, int c ) : x(a), y(b), w(c) {}
};

vector < edge > edges;

void init() {
        for( int i=0; i<sz; i++ ) {
                par[i] = i;
                cnt[i] = 1;
        }
}

int find( int x ) {
        return par[x] = ( x == par[x] ? x : find( par[x] ) );
}

void uni( int x, int y ) {
        x = find( x );
        y = find( y );
        if( x != y ) par[x] = par[y], cnt[y] += cnt[x];
}

void generate( const char* file, int nlim, int qlim, int wlim ) {
        FILE *f = fopen( file, "w+" );
        assert( f != nullptr );

        init();

        fprintf( f, "%d %d\n", nlim, qlim );

        int u, v, w;

        edges.clear();

        for( int i=1; i<nlim; i++ ) {
                u = i + 1;
                v = ( get_rand() % i ) + 1;
                w = ( get_rand() % wlim ) + 1;
                edges.push_back( edge( u, v, w ) );
                uni( u, v );
        }

        random_shuffle( edges.begin(), edges.end() );

        assert( cnt[ find( 1 ) ] == nlim );

        for( const edge& e: edges ) {
                fprintf( f, "%d %d %d\n", e.x, e.y, e.w );
        }

        for( int i=1; i<=qlim; i++ ) {
                u = i + 1;
                v = ( get_rand() % i ) + 1;
                fprintf( f, "%d %d\n", u, v );
        }

        fclose( f );
}

int main() {

        srand( 1337 );

        generate( "input01.txt", 5, 2, 25 );
        generate( "input02.txt", 5, 3, 25 );
        generate( "input03.txt", 100000, 100000, 1000000 );
        generate( "input04.txt", 100000, 100000, 1000000 );
        generate( "input05.txt", 100000, 100000, 1000000 );

        return 0;
}