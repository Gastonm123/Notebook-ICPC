// requisito: max matching bipartito, por defecto Hopcroft-Karp

vector<bool> cover[2];  // nodos cubiertos en ambas partes
// encuentra el min vertex cover del grafo bipartito
// misma complejidad que el algoritmo de max matching bipartito elegido
int konig() {
    cover[0].assign(n,true);
    cover[1].assign(m,false);
    int size = hopkarp();  // alternativamente, también funciona con Kuhn
    auto dfs = [&](auto&& me, int u) -> void {
        cover[0][u] = false;
        for (auto v : g[u]) if (!cover[1][v]) {
            cover[1][v] = true;
            me(me,inv[v]);
        }
    };
    forn(u,n) if (mat[u] < 0) dfs(dfs,u);
    return size;
}
