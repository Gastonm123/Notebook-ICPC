constexpr int MAXN = 20;
int n;
bool adj[MAXN][MAXN];

bool seen[1<<MAXN][MAXN];
bool memo[1<<MAXN][MAXN];
// true sii existe camino simple en el conjunto s que empieza en u
bool hamilton(int s, int u) {
    bool& ans = memo[s][u];
    if (seen[s][u]) return ans;
    seen[s][u] = true, s ^= (1<<u);
    if (s == 0) return ans = true;
    forn(v,n) if (adj[u][v] && (s&(1<<v)) && hamilton(s,v)) return ans = true;
    return ans = false;
}
// true sii existe camino hamiltoniano. complejidad O((1<<n)*n*n)
bool hamilton() {
    forn(s,1<<n) forn(u,n) seen[s][u] = false;
    forn(u,n) if (hamilton((1<<n)-1,u)) return true;
    return false;
}
