int n, r, p[MAXN];    // número de nodos, raíz, y lista de padres
vector<int> g[MAXN];  // lista de adyancencia

vector<bool> cover;
// encuentra el min vertex cover del árbol. complejidad O(n)
void mincover() {
    cover.assign(n,false);
    auto dfs = [&](auto&& me, int u) -> bool {
        for (auto v : g[u]) if (v != p[u] && !me(me,v)) cover[u] = true;
        return cover[u];
    };
    dfs(dfs,r);
}
