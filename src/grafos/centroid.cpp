int sz[MAXN], ft[MAXN], tk[MAXN];
void calcsz(int u, int p) {
    sz[u] = 1;
    for (auto v : g[u]) if (v!=p && !tk[v]) {
        calcsz(v, u);
        sz[u]+=sz[v];
    }
}
int dfs(int u, int p) {
    int pesado = -1;
    for (auto v : g[u]) if (v!=p && !tk[v])  {
        if (pesado==-1 || sz[pesado]<sz[v]) pesado = v;
    }
    if (pesado==-1) return u;
    if (sz[pesado]<=sz[u]/2) {
        tk[u] = true;
        for (auto v : g[u]) if (!tk[v]) {
            int c=dfs(v, u);
            ft[c]=u;
        }
        return u;
    } else {
        int sz_pesado=sz[pesado];
        sz[pesado]=sz[u];
        sz[u]-=sz_pesado;
        return dfs(pesado, u);
    }
}