// https://cses.fi/problemset/task/1130

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

int n, r, p[MAXN];
vector<int> g[MAXN];

vector<int> match;
void maxmatch() {
    match.assign(n,-1);
    auto dfs = [&](auto&& me, int u) -> int {
        for (auto v : g[u]) if (v != p[u])
            if (match[u] == me(me,v)) match[u] = v, match[v] = u;
        return match[u];
    };
    dfs(dfs,r);
}

void root(int u) { for (auto v : g[u]) if (v != p[u]) p[v] = u, root(v); }

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    forn(j,n-1) {
        int u, v;
        cin >> u >> v, --u, --v;
        g[u].pb(v), g[v].pb(u);
    }

    root(r=0);
    maxmatch();
    int ans = 0;
    forn(u,n) ans += match[u] > u;

    cout << ans << endl;
}
