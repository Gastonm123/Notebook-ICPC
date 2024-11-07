int n, m;             // número de nodos en ambas partes
vector<int> g[MAXN];  // lista de adyacencia [0,n) -> [0,m)

int mat[MAXN];  // matching [0,n) -> [0,m)
int inv[MAXM];  // matching [0,m) -> [0,n)
// encuentra el max matching del grafo bipartito
// complejidad O(sqrt(n+m)*e), donde e es el número de aristas
int hopkarp() {
    fill(mat,mat+n,-1);
    fill(inv,inv+m,-1);
    int size = 0;
    vector<int> d(n);
    auto bfs = [&] {
        bool aug = false;
        queue<int> q;
        forn(u,n) if (mat[u] < 0) q.push(u); else d[u] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (inv[v] < 0) aug = true;
                else if (d[inv[v]] < 0) d[inv[v]] = d[u] + 1, q.push(inv[v]);
            }
        }
        return aug;
    };
    auto dfs = [&](auto&& me, int u) -> bool {
        for (auto v : g[u]) if (inv[v] < 0) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        for (auto v : g[u]) if (d[inv[v]] > d[u] && me(me,inv[v])) {
            mat[u] = v, inv[v] = u;
            return true;
        }
        d[u] = 0;
        return false;
    };
    while (bfs()) forn(u,n) if (mat[u] < 0) size += dfs(dfs,u);
    return size;
}
