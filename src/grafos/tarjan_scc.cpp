vector<int> g[MAXN], ss;
int n, num, order[MAXN], lnk[MAXN], nsc, cmp[MAXN];
void scc(int u) {
    order[u] = lnk[u] = ++num;
    ss.pb(u); cmp[u] = -2;
    for (auto v : g[u]) {
        if (order[v] == 0) {
            scc(v);
            lnk[u] = min(lnk[u], lnk[v]);
        }
        else if (cmp[v] == -2) {
            lnk[u] = min(lnk[u], lnk[v]);
        }
    }
    if (lnk[u] == order[u]) {
        int v;
        do { v = ss.back(); cmp[v] = nsc; ss.pop_back(); }
        while (v != u);
        nsc++;
    }
}
void tarjan() {
    memset(order, 0, sizeof(order)); num = 0;
    memset(cmp, -1, sizeof(cmp)); nsc = 0;
    forn (i, n) if (order[i] == 0) scc(i);
}