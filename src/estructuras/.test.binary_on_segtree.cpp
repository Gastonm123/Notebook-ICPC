// https://codeforces.com/gym/100513/problem/C


#include <bits/stdc++.h>
#define forr(i,a,n) for(int i=(a); i<(n); i++)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,n) for(int i=(n)-1;i>=(a);i--)
#define dforn(i,n) dforr(i,0,n)
#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)
#define sz(v) ((int)v.size())
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
using namespace std;
using ll = long long;
using pii = pair<int,int>;

const int MAXN=3e5+1;
using tipo=unordered_set<int>;
tipo neutro = {};
tipo oper(tipo a, tipo b) {
    tipo c;
    for (auto x : a) c.insert(x);
    for (auto x : b) c.insert(x);
    return c;
}
struct RMQ {
    int sz;
    tipo t[4*MAXN];
    tipo &operator[](int p) { return t[sz+p]; }
    void init(int n) {
        sz = 1<<(32-__builtin_clz(n));
        forn (i, 2*sz) t[i] = neutro;
    }
    void updall() {dforn(i,sz)t[i]=oper(t[2*i],t[2*i+1]);}
} segtree;
#define includes(bolsa,t) (bolsa.count(t))
typedef int Val;
// invertimos la busqueda: primero en el hijo derecho
int search_first(RMQ &rmq, Val v, int i, int j, int n, int a, int b) {
    if (j<=a || i>=b) return -1;
    if (n>=rmq.sz) return includes(rmq.t[n],v) ? n-rmq.sz : -1;
    int c=(a+b)/2;
    if (i<=a && b<=j) {
        if (includes(rmq.t[2*n+1],v))
            return search_first(rmq,v,i,j,2*n+1,c,b);
        else
            return search_first(rmq,v,i,j,2*n,a,c);
    }
    int res=search_first(rmq,v,i,j,2*n+1,c,b);
    if (res!=-1) return res;
    res=search_first(rmq,v,i,j,2*n,a,c);
    return res;
}
int search_first(RMQ &rmq, Val v, int i, int j) {return search_first(rmq,v,i,j,1,0,rmq.sz);}
unordered_map<string, string> datos[MAXN];
vector<int> g[MAXN];
int wg[MAXN],dad[MAXN],dep[MAXN];
void dfs1(int x){
    wg[x]=1;
    for (int y:g[x]) if(y!=dad[x]) {
        dad[y]=x; dep[y]=dep[x]+1; dfs1(y);
        wg[x]+=wg[y];
    }
}
int curpos,pos[MAXN],head[MAXN],nodo[MAXN];
void hld(int x,int c) {
    if (c<0) c=x;
    nodo[curpos]=x; pos[x]=curpos++; head[x]=c;
    int mx=-1;
    for (int y:g[x]) if(y!=dad[x] && (mx<0||wg[mx]<wg[y])) mx=y;
    if (mx>=0) hld(mx,c);
    for (int y:g[x]) if(y!=mx&&y!=dad[x]) hld(y,-1);
}
void hld_init() {dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}
// query de la primera aparicion de un string en el camino de x a la raiz
int query(int x, int id_target, RMQ& rmq){
    // if (datos[x].count(target)) return x;
    const int RAIZ=0;
    while(head[x]!=head[RAIZ]) {
        // cout << pos[head[x]] << " " << pos[x]+1 << endl;
        int r = search_first(rmq,id_target,pos[head[x]],pos[x]+1);
        if (r!=-1) return r;
        x=dad[head[x]];
    }
    int r = search_first(rmq,id_target,pos[head[x]],pos[x]+1);
    if (r!=-1) return r;
    return RAIZ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> keys;
    int n;
    cin >> n;
    forn (i, n) {
        int p, k; cin >> p >> k;
        if (i>0)
            g[p-1].pb(i);
        forn (j, k) {
            string aux;
            string a, b;
            cin >> aux;
            bool igual = false;
            forn (ii, sz(aux)) {
                if (aux[ii]=='=') {
                    igual=true;
                    continue;
                }
                if (!igual) a.pb(aux[ii]);
                else b.pb(aux[ii]);
            }
            keys.push_back(a);
            datos[i][a]=b;
        }
    }

    sort(all(keys));

    hld_init();
    segtree.init(n);
    forn (i, n) {
        for (auto &[key, val] : datos[i]) {
            int id = lower_bound(all(keys),key) - begin(keys);
            segtree[pos[i]].insert(id);
        }
    }
    segtree.updall();

    int q;
    cin >> q;
    forn (i, q) {
        int start;
        string target;
        cin >> start >> target;
        start--;
        auto it = lower_bound(all(keys),target);
        string res="N/A";
        if (it!=end(keys) && *it==target) {
            int id = it-begin(keys);
            int pos = query(start,id,segtree);
            if (includes(datos[nodo[pos]], target))
                res = datos[nodo[pos]][target];
        }
        cout << res << endl;
    }
}