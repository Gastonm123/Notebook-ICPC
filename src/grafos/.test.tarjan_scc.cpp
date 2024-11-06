// https://codeforces.com/gym/102501/problem/K

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

const int MAXN = 1e5;

vector<int> g[MAXN], ss;
int num, order[MAXN], lnk[MAXN], nsc, cmp[MAXN];
int n;
void scc(int u) {
    order[u] = lnk[u] = ++num;
    ss.pb(u); cmp[u] = -2;
    for (auto v : g[u]) {
        if (order[v] == 0) {
            scc(v);
            lnk[u] = min(lnk[u], lnk[v]);
        }
        else if (cmp[v] == -2) {
            lnk[u] = min(lnk[u], lnk[v]);
        }
    }
    if (lnk[u] == order[u]) {
        int v;
        do { v = ss.back(); cmp[v] = nsc; ss.pop_back(); }
        while (v != u);
        nsc++;
    }
}
void tarjan() {
    memset(order, 0, sizeof(order)); num = 0;
    memset(cmp, -1, sizeof(cmp)); nsc = 0;
    forn (i, n) if (order[i] == 0) scc(i);
}

vector<int> visited, ans, target;
int T;
set<int> s;

void aux_solve(int u){
    visited[u] = 1;
    for (auto v : g[u]) {
        if (!visited[v]) aux_solve(v);
        if (cmp[u]==cmp[v]) continue;
        if (target[cmp[v]]) ans[cmp[u]] = 1;
        else if (ans[cmp[v]] == 1) ans[cmp[u]] = 1;
    }
}

void solve(){
    visited.resize(n,0);
    ans.resize(n,-1);
    target.resize(n,0);
    visited[T] =1;
    vector<int> aux(n,0);
    for(int i : s){
        target[cmp[i]] = 1;
        aux[cmp[i]]++;
        if (aux[cmp[i]]>1) ans[cmp[i]] = 1;
    }
    for(int i : s){
        if (!visited[i]) aux_solve(i);
    }
}



int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int m;
    cin >>n>>m>>T;
    forn(i,m){
        int a,b;
        cin>>a>>b;
        if(b==T){
            s.insert(a);
        }
        if(a!=T && b!=T) {
            g[a].pb(b);
        }
    }
    tarjan();
    solve();
    vector<int> especiales;
    for (auto i : s) {
        if(ans[cmp[i]] == -1){
            especiales.pb(i);
        }
    }
    cout<< especiales.size()<<"\n";
    for(int i : especiales){
        cout << i<< "\n";
    }
    return 0;
}