int n, m;             // número de nodos en ambas partes
vector<int> g[MAXN];  // lista de adyacencia [0,n) -> [0,m)

int mat[MAXN];  // matching [0,n) -> [0,m)
int inv[MAXM];  // matching [0,m) -> [0,n)
// encuentra el max matching del grafo bipartito
// complejidad O(n*e), donde e es el número de aristas
int kuhn() {
    fill(mat,mat+n,-1);
    fill(inv,inv+m,-1);
    int root, size = 0;
    vector<int> seen(n,-1);
    auto dfs = [&](auto&& me, int u) -> bool {
        seen[u] = root;
        for (auto v : g[u]) if (inv[v] < 0) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        for (auto v : g[u]) if (seen[inv[v]] < root && me(me,inv[v])) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        return false;
    };
    forn(u,n) size += dfs(dfs,root=u);
    return size;
}
