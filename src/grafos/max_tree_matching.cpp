int n, r, p[MAXN];    // número de nodos, raíz, y lista de padres
vector<int> g[MAXN];  // lista de adyancencia

int match[MAXN];
// encuentra el max matching del árbol. complejidad O(n)
int maxmatch() {
    fill(match,match+n,-1);
    int size = 0;
    auto dfs = [&](auto&& me, int u) -> int {
        for (auto v : g[u]) if (v != p[u])
            if (match[u] == me(me,v)) match[u] = v, match[v] = u;
        size += match[u] >= 0;
        return match[u];
    };
    dfs(dfs,r);
    return size;
}
