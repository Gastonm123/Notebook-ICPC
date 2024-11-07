int n, r, p[MAXN];    // número de nodos, raíz, y lista de padres
vector<int> g[MAXN];  // lista de adyancencia

vector<int> match;
// encuentra el max matching del árbol. complejidad O(n)
void maxmatch() {
    match.assign(n,-1);
    auto dfs = [&](auto&& me, int u) -> int {
        for (auto v : g[u]) if (v != p[u])
            if (match[u] == me(me,v)) match[u] = v, match[v] = u;
        return match[u];
    };
    dfs(dfs,r);
}
