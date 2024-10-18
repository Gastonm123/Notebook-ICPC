int n;
vector<int> g[MAXN];

vector<int> depth, etour, vtime;

// operación de la sparse table, escribir `#define oper lca_oper`
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
