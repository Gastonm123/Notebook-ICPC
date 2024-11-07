// https://codeforces.com/problemset/problem/1144/F

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

constexpr int MAXN = 200'000;

int n;
vector<int> g[MAXN];

bool color[MAXN];
bool bicolor() {
    vector<bool> seen(n);
    auto dfs = [&](auto&& me, int u, bool c) -> bool {
        color[u] = c, seen[u] = true;
        for (int v : g[u]) {
            if (seen[v] && color[v] == color[u]) return false;
            if (!seen[v] && !me(me,v,!c)) return false;
        }
        return true;
    };
    forn(u,n) if (!seen[u] && !dfs(dfs,u,0)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    int m;
    cin >> m;
    vector<pair<int, int>> es;
    es.reserve(m);
    forn(j,m) {
        int u, v;
        cin >> u >> v, --u, --v;
        g[u].pb(v);
        g[v].pb(u);
        es.emplace_back(u,v);
    }

    if (bicolor()) {
        cout << "YES" << endl;
        for (auto [u,v] : es) cout << color[u];
        cout << endl;
    } else cout << "NO" << endl;
}
