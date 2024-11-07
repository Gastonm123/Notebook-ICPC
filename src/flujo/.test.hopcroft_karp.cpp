// https://judge.yosupo.jp/problem/bipartitematching

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

constexpr int MAXN = 100'000, MAXM = MAXN;

int n, m;
vector<int> g[MAXN];

int mat[MAXN];
int inv[MAXM];
int hopkarp() {
    fill(mat,mat+n,-1);
    fill(inv,inv+m,-1);
    int size = 0;
    vector<int> d(n);
    auto bfs = [&] {
        bool aug = false;
        queue<int> q;
        forn(u,n) if (mat[u] < 0) q.push(u); else d[u] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (inv[v] < 0) aug = true;
                else if (d[inv[v]] < 0) d[inv[v]] = d[u] + 1, q.push(inv[v]);
            }
        }
        return aug;
    };
    auto dfs = [&](auto&& me, int u) -> bool {
        for (auto v : g[u]) if (inv[v] < 0) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        for (auto v : g[u]) if (d[inv[v]] > d[u] && me(me,inv[v])) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        d[u] = 0;
        return false;
    };
    while (bfs()) forn(u,n) if (mat[u] < 0) size += dfs(dfs,u);
    return size;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    int e;
    cin >> e;
    forn(j,e) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
    }

    int size = hopkarp();

    cout << size << endl;
    forn(u,n) if (mat[u] >= 0) cout << u << ' ' << mat[u] << endl;
}
