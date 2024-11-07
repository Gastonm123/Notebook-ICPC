// https://www.hackerearth.com/practice/algorithms/graphs/hamiltonian-path/practice-problems/algorithm/micro-and-coins/

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

constexpr int MAXN = 20;
int n;
bool adj[MAXN][MAXN];

bool seen[1<<MAXN][MAXN];
bool memo[1<<MAXN][MAXN];
bool hamilton(int s, int u) {
    bool& ans = memo[s][u];
    if (seen[s][u]) return ans;
    seen[s][u] = true, s ^= (1<<u);
    if (s == 0) return ans = true;
    forn(v,n) if (adj[u][v] && (s&(1<<v)) && hamilton(s,v)) return ans = true;
    return ans = false;
}
bool hamilton() {
    forn(s,1<<n) forn(u,n) seen[s][u] = false;
    forn(u,n) if (hamilton((1<<n)-1,u)) return true;
    return false;
}

void solve() {

    int m;
    cin >> n >> m;
    memset(adj,false,sizeof(adj));
    forn(j,m) {
        int u, v;
        cin >> u >> v, --u, --v;
        adj[u][v] = adj[v][u] = true;
    }

    if (hamilton()) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}
