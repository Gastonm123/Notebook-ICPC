//Problema I https://codeforces.com/gym/101889/
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b)  for(int i = int(a); i < int(b); i++)
#define forn(i,n)    forr(i,0,n)
#define dforn(i, n) for(int i =n-1; i>=0; i--)
#define all(v)       begin(v), end(v)
#define mp           make_pair
#define sz(v)        int(v.size())
#define pb           push_back
#define fst          first
#define snd          second
#define endl         '\n'
#define dprint(x)    cerr << #x << " = " << (x) << endl
using ll = long long;

const int MAXN=2*1e5+1;

#define oper max
const int neutro=-1;
#define tipo int

struct RMQ{
	int sz;
	tipo t[4*MAXN];
	tipo &operator[](int p){return t[sz+p];}
	void init(int n){ // O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forn(i, 2*sz) t[i]=neutro;
	}
	void updall(){dforn(i, sz) t[i]=oper(t[2*i], t[2*i+1]);} // O(N)
	tipo get(int i, int j){return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b){ // O(lgn)
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return oper(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	void set(int p, tipo val){ // O(lgn)
		for(p+=sz; p>0 && t[p]!=val;){
			t[p]=val;
			p/=2;
			val=oper(t[p*2], t[p*2+1]);
		}
	}
};

RMQ rmq;
vector<int> g[MAXN];
int wg[MAXN],dad[MAXN],dep[MAXN]; // weight,father,depth

void dfs1(int x){
	wg[x]=1;
	for(int y:g[x])if(y!=dad[x]){
		dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
		wg[x]+=wg[y];
	}
}
int curpos,pos[MAXN],head[MAXN];
void hld(int x, int c){
	if(c<0)c=x;
	pos[x]=curpos++;head[x]=c;
	int mx=-1;
	for(int y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
	if(mx>=0)hld(mx,c);
	for(int y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
}
void hld_init(){dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}
int query(int x, int y, RMQ& rmq){
	int r=neutro; //neutro del rmq
	while(head[x]!=head[y]){
		if(dep[head[x]]>dep[head[y]])swap(x,y);
		r=oper(r,rmq.get(pos[head[y]],pos[y]+1));
		y=dad[head[y]];
	}
	if(dep[x]>dep[y])swap(x,y); // now x is lca
	r=oper(r,rmq.get(pos[x]+1,pos[y]+1));
	return r;
}

struct UnionFind {
    int rep[MAXN];
    void init() {forn(i, MAXN) rep[i] = i;}
    void join(int a, int b) {
        rep[find(a)] = find(b);
    }
    int find(int a) {
        if (rep[a] == a) return a;
        return rep[a] = find(rep[a]);
    }
};

UnionFind uf;
ll peso_arbol;
map<pair<int,int>,int> pesos;


struct Comp {
    bool operator() (const tuple<int,int,int> a, const tuple<int,int,int> b) const {
        return get<2>(a) < get<2>(b);
    }
};

int main (int argc, char** argv) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;
    vector<tuple<int,int,int>> aristas;
    forn(i, m) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        aristas.pb({a,b,c});
        pesos[{a,b}] = c;
        pesos[{b,a}] = c;
    }

    sort(all(aristas), Comp());
    uf.init(); rmq.init(n+1);
    vector<tuple<int,int,int>> aristas_arbol;
    forn (i, m) {
        auto a = get<0>(aristas[i]);
        auto b = get<1>(aristas[i]);
        auto c = get<2>(aristas[i]);
        if (uf.find(a) != uf.find(b)) {
            uf.join(a, b);
            g[a].pb(b);
            g[b].pb(a);
            aristas_arbol.pb({a,b,c});
            peso_arbol+=c;
        }
    }
    hld_init(); 
    for(auto [a,b,c] : aristas_arbol){
        if(dep[a] > dep[b]) rmq[pos[a]] = c;
        else rmq[pos[b]]=c;
    }
    rmq.updall();
    int q; cin >> q;
    forn (i, q) {
        int u, v; cin >> u >> v;
        u--, v--;
        int res = query(v,u,rmq);
        cout << peso_arbol - res + pesos[{u,v}] << endl;
    }
    return 0;
}