// https://vjudge.net/problem/UVA-315

#include <bits/stdc++.h>
#define forn(i, n) for(int i =0;i<(n);i++)
#define forr(i,a,n) for(int i =(a);i<(n);i++)
#define dforn(i, n) for(int i =(n)-1; i>=0; i--)
#define mp make_pair
#define all(x) begin(x),end(x)
#define sz(x) (x.size())
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e5+10;

void handle_bridge(int u, int v) {}

// solo para grafos no dirigidos
vector<int> g[MAXN];
int n, num, order[MAXN], lnk[MAXN], art[MAXN];
void bridge_art(int u, int p) {
    order[u] = lnk[u] = ++num;
    for (auto v : g[u]) if (v != p) {
        if (order[v] == 0) {
            bridge_art(v, u);
            if (lnk[v] >= order[u])       // para puntos de
                art[u] = 1;               // articulacion.
            if (lnk[v] > order[u])        // para puentes.
                handle_bridge(u, v);
        }
        lnk[u] = min(lnk[u], lnk[v]);
    }
}
int run() {
    memset(order, 0, sizeof(order));
    memset(art, 0, sizeof(art)); num = 0;
    forn (i, n) {
        if (order[i] == 0) {
            bridge_art(i, -1);
            art[i] = (sz(g[i]) > 1);
        }
    }
    int ans = 0; forn (i, n) if (art[i]) ans++;
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    while (cin >> n) {
        if (n == 0) break;
        for (;;) {
            int v; cin >> v;
            if (v == 0) break;
            string s; getline(cin, s);
            stringstream ss(s);
            int u; v--;
            while (ss >> u) {
                u--; g[u].pb(v); g[v].pb(u);
            }
        }
        cout << run() << endl;
        forn (i, n) g[i].clear();
    }
}