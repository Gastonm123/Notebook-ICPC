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