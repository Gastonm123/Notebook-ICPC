// https://cses.fi/problemset/task/1688

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
#define dprint(v) cout << #v " = " << v << endl

typedef long long ll;
typedef pair<int, int> pii;

constexpr int MAXN = 2e5;

vector<int> depth;
int lca_oper(int u, int v) { return depth[u]<depth[v] ? u : v; };
#define oper lca_oper
constexpr int K = 19;
int st[K][1<<K];
void st_init(vector<int>& a) {
    int n = sz(a);
    forn(i,n) st[0][i] = a[i];
    forr(k,1,K) forn(i,n-(1<<k)+1)
        st[k][i] = oper(st[k-1][i], st[k-1][i+(1<<(k-1))]);
}
int st_query(int l, int r) {
    int k = 31-__builtin_clz(r-l);
    return oper(st[k][l], st[k][r-(1<<k)]);
}

int n;
vector<int> g[MAXN];

vector<int> etour, vtime;
void lca_dfs(int u) {
    vtime[u] = sz(etour), etour.push_back(u);
    for (auto v : g[u]) {
        if (vtime[v] >= 0) continue;
        depth[v] = depth[u]+1; lca_dfs(v); etour.push_back(u);
    }
}
auto lca_init(int root) {
    depth.assign(n,0), etour.clear(), vtime.assign(n,-1);
    lca_dfs(root); st_init(etour);
}

auto lca(int u, int v) {
    int l = min(vtime[u],vtime[v]);
    int r = max(vtime[u],vtime[v])+1;
    return st_query(l,r);
}
int dist(int u, int v) { return depth[u]+depth[v]-2*depth[lca(u,v)]; }

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int q;
    cin >> n >> q;
    forr(u,1,n) {
        int pu;
        cin >> pu, --pu;
        g[u].push_back(pu);
        g[pu].push_back(u);
    }
    lca_init(0);
    forn(qid,q) {
        int u, v;
        cin >> u >> v, --u, --v;
        cout << lca(u,v)+1 << endl;
    }
}
