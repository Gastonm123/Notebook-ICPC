// LCA O(1) con sparse table.
// operación de la sparse table, escribir `#define oper lca_oper`
int n;
vector<int> g[MAXN];
vector<int> depth, etour, vtime;
int lca_oper(int u, int v) { return depth[u]<depth[v] ? u : v; };
void lca_dfs(int u) {
    vtime[u] = sz(etour), etour.push_back(u);
    for (auto v : g[u]) {
        if (vtime[v] >= 0) continue;
        depth[v] = depth[u]+1; lca_dfs(v); etour.push_back(u);
    }
}
auto lca_init(int root) {
    depth.assign(n,0), etour.clear(), vtime.assign(n,-1);
    lca_dfs(root); st_init(etour);
}
auto lca(int u, int v) {
    int l = min(vtime[u],vtime[v]);
    int r = max(vtime[u],vtime[v])+1;
    return st_query(l,r);
}
int dist(int u, int v) { return depth[u]+depth[v]-2*depth[lca(u,v)]; }

// LCA O(logn) con binary lifting.
vector<int> g[1<<K]; int n; // K such that 2^K>=n
int F[K][1<<K], D[1<<K];
void lca_dfs(int x){
    forn(i, sz(g[x])){
        int y = g[x][i]; if(y==F[0][x]) continue;
        F[0][y]=x; D[y]=D[x]+1;lca_dfs(y);
    }
}
void lca_init(){
    D[0]=0;F[0][0]=-1;
    lca_dfs(0);
    forr(k,1,K)forn(x,n)
        if(F[k-1][x]<0)F[k][x]=-1;
        else F[k][x]=F[k-1][F[k-1][x]];
}
int lca(int x, int y){
    if(D[x]<D[y])swap(x,y);
    for(int k = K-1;k>=0;--k) if(D[x]-(1<<k) >=D[y])x=F[k][x];
    if(x==y)return x;
    for(int k=K-1;k>=0;--k)if(F[k][x]!=F[k][y])x=F[k][x],y=F[k][y];
    return F[0][x];
}
int dist(int x, int y){
    return D[x] + D[y] - 2*D[lca(x,y)];
}
