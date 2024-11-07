int n;
vector<int> g[MAXN];

bool color[MAXN];
bool bicolor() {
    vector<bool> seen(n);
    auto dfs = [&](auto&& me, int u, bool c) -> bool {
        color[u] = c, seen[u] = true;
        for (int v : g[u]) {
            if (seen[v] && color[v] == color[u]) return false;
            if (!seen[v] && !me(me,v,!c)) return false;
        }
        return true;
    };
    forn(u,n) if (!seen[u] && !dfs(dfs,u,0)) return false;
    return true;
}
