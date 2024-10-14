//https://codeforces.com/gym/104945/problem/B

#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b)  for(int i = int(a); i < int(b); i++)
#define forn(i,n)    forr(i,0,n)
#define dforn(i,n)   for(int i=n-1; i>=0; i--)
#define all(v)       begin(v), end(v)
#define mp           make_pair
#define sz(v)        int(v.size())
#define pb           push_back
#define fst          first
#define snd          second
#define endl         '\n'
#define dprint(x)    cerr << #x << " = " << (x) << endl

using ll = long long;
const int MAXN =3001;

vector<int> g[MAXN];
vector<bool> vis;
vector<int> match; 

bool kuhn_dfs(int u){
    if (vis[u]) return false;
    vis[u] = true;
    for (int v : g[u]) if (match[v] == -1 || kuhn_dfs(match[v])) {
        match[v] = u;
        return true;
    } return false;
}



vector<int> kuhn(int n) {
    match.resize(n, -1);
    vis.resize(n);
    forn(u, n) {
        vis.assign(n, false);
        kuhn_dfs(u);
    }
    return match;
}

int main (int argc, char** argv) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (argc == 2) freopen(argv[1], "r", stdin);
    int n, m;
    cin >> n >> m;
    forn(i, n){
        int k; cin >> k;
        forn(c,k){
            int ci; cin >> ci; g[i].pb(ci-1+n); g[ci-1+n].pb(i);
        }
    }
    auto res = kuhn(n+m);
    int cant = 0;
    for(auto k : res) if(k != -1) cant++;
    cout << cant/2<< endl;
    return 0;
}