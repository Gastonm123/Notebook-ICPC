bool vis[MAXN]; //para centroides
vector<int> g[MAXN]; int size[MAXN];
vector<int> g1[MAXN]; //para centroides
void calcsz(int u, int p) {
    size[u] = 1;
    for (int v : g[u]) if (v != p && !vis[v]) {
        calcsz(v, u); size[u] += size[v]; }
}
int cendfs(int u, int p, int ts) {
    int maximo = 0, pesado, r;
    for (int v : g[u]) if (v != p && !vis[v]) {
        if (maximo < size[v]) {
            maximo = size[v]; pesado = v; }
    }
    if (maximo <= (ts/2)) {
        vis[u] = true;
        for (int v : g[u]) if (!vis[v]) {
            if (v == p) calcsz(v, u);
            r = cendfs(v, u, hijos[v]);
            add_edge(g1, u, r);
        }
        r = u;
    }
    else r = cendfs(pesado, u, ts);
    return r;
}
// euler para responder en el arbol de centroides
int te[MAXN], ts[MAXN]; vector<Partial> euler;
void do_euler(int u, int p, Partial &p) {
    te[u] = sz(euler); euler.pb(c);
    for (int v : g[u]) if (v != p && !vis[v]) {
        do_euler(v, u, p); } //cambiar p
    ts[u] = sz(euler);
}
Sol oncen(int u, int p) {
    do_euler(u, p, Partial{});
    vis[u] = true; //no tocar visitados
    Sol r{};
    for (int v : g1[u]) if (v != p) {
        r = max(r, oncen(v, u)); }
    return r;
}