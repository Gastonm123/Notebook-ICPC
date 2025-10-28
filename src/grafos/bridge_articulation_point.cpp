// solo para grafos no dirigidos
vector<int> g[MAXN];
int n, num, root, rootChildren;
int order[MAXN], lnk[MAXN], art[MAXN];
void bridge_art(int u, int p) {
    order[u] = lnk[u] = ++num;
    for (auto v : g[u]) if (v != p) {
        if (u == root) rootChildren++;
        if (order[v] == 0) {
            bridge_art(v, u);
            if (lnk[v] >= order[u])       // para puntos de
                art[u] = 1;               // articulacion.
            if (lnk[v] > order[u])        // para puentes.
                handle_bridge(u, v);
        }
        lnk[u] = min(lnk[u], lnk[v]);
    }
}
void run() {
    memset(order, 0, sizeof(order));
    memset(art, 0, sizeof(art)); num = 0;
    forn (i, n) {
        if (order[i] == 0) {
            root = i; bridge_art(i, -1);
            art[i] = (rootChildren > 1);
        }
    }
}