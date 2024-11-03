//https://cses.fi/problemset/task/1672/

#include <bits/stdc++.h>
using namespace std;
#define forr(i, a, b) for (int i = int(a); i < int(b); i++)
#define forn(i, n) forr(i,0,n)
#define dforr(i, a, b) for (int i = int(b)-1; i >= int(a); i--)
#define dforn(i, n) dforr(i,0,n)
#define all(v) begin(v),end(v)
#define sz(v) (int(size(v)))
#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define endl '\n'
#define dprint(v) cerr << #v " = " << v << endl

typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 500;
const ll INF = 1e15;
// g[i][j]: weight of edge (i, j) or INF if there's no edge
// g[i][i]=0
ll g[MAXN][MAXN];int n;
void floyd(){ // O(n^3) . Replaces g with min distances
	forn(k,n)forn(i,n)if(g[i][k]<INF)forn(j,n)if(g[k][j]<INF)
		g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
bool inNegCycle(int v){return g[v][v]<0;}
bool hasNegCycle(int a, int b){ // true iff there's neg cycle in between
	forn(i,n)if(g[a][i]<INF&&g[i][b]<INF&&g[i][i]<0)return true;
	return false;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int m, q; cin >> n >> m >> q;
    forn(i, n) forn(j, n) g[i][j] = INF;
    forn(i, n) g[i][i] = 0;
    forn(i, m){
        int u, v; ll c; cin >> u >> v >> c;
        u--;v--;
        g[u][v] = min(g[u][v],c);
        g[v][u] = min(g[v][u],c);;
    }
    floyd();
    forn(qqq, q){
        int u, v; cin >> u >> v;
        u--;v--;
        if(g[u][v] == INF) cout << -1 << endl;
        else cout << g[u][v] << endl;
    }
}
