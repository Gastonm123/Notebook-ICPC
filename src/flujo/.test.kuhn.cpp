// https://codeforces.com/gym/104945/problem/B

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

constexpr int MAXN = 1000, MAXM = 100;

int n, m;
vector<int> g[MAXN];

int mat[MAXN];
int inv[MAXM];
int kuhn() {
    fill(mat,mat+n,-1);
    fill(inv,inv+m,-1);
    int root, size = 0;
    vector<int> seen(n,-1);
    auto dfs = [&](auto&& me, int u) -> bool {
        seen[u] = root;
        for (auto v : g[u]) if (inv[v] < 0) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        for (auto v : g[u]) if (seen[inv[v]] < root && me(me,inv[v])) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        return false;
    };
    forn(u,n) size += dfs(dfs,root=u);
    return size;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    forn(i,n) {
        int k;
        cin >> k;
        forn(cid,k) {
            int c;
            cin >> c, --c;
            g[i].pb(c);
        }
    }

    cout << kuhn() << endl;
}
