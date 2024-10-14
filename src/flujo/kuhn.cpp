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
} //n: cant de nodos    devuelve un vector con -1 si no matchea y sino su match