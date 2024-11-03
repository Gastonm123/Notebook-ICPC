//https://cses.fi/problemset/task/1693/

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
const int MAXN =1e5+10;
// Directed version (uncomment commented code for undirected)
struct edge {
	int y;
//	list<edge>::iterator rev;
	edge(int y):y(y){}
};
list<edge> g[MAXN];
void add_edge(int a, int b){
	g[a].push_front(edge(b));//auto ia=g[a].begin();
//	g[b].push_front(edge(a));auto ib=g[b].begin();
//	ia->rev=ib;ib->rev=ia;
}
vector<int> p;
void go(int x){
	while(g[x].size()){
		int y=g[x].front().y;
		//g[y].erase(g[x].front().rev);
		g[x].pop_front();
		go(y);
	}
	p.push_back(x);
}
vector<int> get_path(int x){ // get a path that begins in x
// check that a path exists from x before calling to get_path!
	p.clear();go(x);reverse(p.begin(),p.end());
	return p;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> deg(n,0);
    forn(i,m){
        int a, b; cin >> a >> b;
        a--;b--;
        add_edge(a,b);
        deg[a]--;
        deg[b]++;
    }
    bool f = deg[0] == -1 && deg[n-1] == 1;
    forr(i,1, n-1){
        f &= deg[i] == 0;
    }
    if(!f) cout << "IMPOSSIBLE" << endl;
    else{
        auto p = get_path(0);
        if(sz(p) != m+1) {cout << "IMPOSSIBLE" << endl; return 0;}
        for(auto i : p) cout << i+1 << " ";
        cout << endl;
    }
}
