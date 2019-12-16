#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 1e4 + 5;
const int inf = 1e9;

int n, m, cnt;
ii lmao[N];

vector< ii > graph[N];

long long ans = 0;

struct DSU {
    int pSet[N];
    DSU() {
        for(int i = 0; i < N; i++)
            pSet[i] = i;
    }
    int findSet( int u ) {
        if( u == pSet[u] ) return u;
        else return pSet[u] = findSet( pSet[u] );
    }
    void unionSet( int u, int v ) {
        u = findSet(u), v = findSet(v);
        pSet[u] = v;
    }
}dsu;

int main() {
    cin.tie(0), ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].pb( mp( w, v ) );
        graph[v].pb( mp( w, u ) );
    }
    cnt = n;
    while( cnt > 1 ) {
        for(int i = 1; i <= n; i++)
            lmao[i] = mp( inf, inf );
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < (int)( graph[i].size() ); j++) {
                int v = graph[i][j].se;
                if( dsu.findSet(i) == dsu.findSet(v) ) continue;
                lmao[dsu.findSet(i)] = min( lmao[dsu.findSet(i)], graph[i][j] );
                lmao[dsu.findSet(v)] = min( lmao[dsu.findSet(v)], graph[i][j] );
            }
        }
        for(int i = 1; i <= n; i++) {
            if( lmao[dsu.findSet(i)].fi == inf ) continue;
            if( dsu.findSet( i ) == dsu.findSet( lmao[dsu.findSet(i)].se ) ) continue;
            ans += lmao[dsu.findSet(i)].fi;
            dsu.unionSet( i, lmao[dsu.findSet(i)].se );
            cnt--;
        }
    }
    cout << ans;
}
