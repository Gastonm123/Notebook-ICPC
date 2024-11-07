int n, r, p[MAXN];    // número de nodos, raíz, y lista de padres
vector<int> g[MAXN];  // lista de adyancencia

bool cover[MAXN];
// encuentra el min vertex cover del árbol. complejidad O(n)
int mincover() {
    fill(cover,cover+n,false);
    int size = 0;
    auto dfs = [&](auto&& me, int u) -> bool {
        for (auto v : g[u]) if (v != p[u] && !me(me,v)) cover[u] = true;
        size += cover[u];
        return cover[u];
    };
    dfs(dfs,r);
    return size;
}
