vector<pair<int,int>> g[MAXN];  // u->[(v,cost)]
ll dist[MAXN];
void kcolas(int x, int max_dist){
	memset(dist,-1,sizeof(dist));
    const int K=max_dist+1;
    vector<vector<pii>> colas(K);
    colas[0].pb({0,x});
    dist[x]=0;
    for (int cola_actual=0, ult_cola=-1; ; cola_actual = (cola_actual+1)%K) {
        if (ult_cola == cola_actual) break; // dimos la vuelta
        if (colas[cola_actual].size()) ult_cola = cola_actual;
        while (colas[cola_actual].size()) {
            auto [d,x]=colas[cola_actual].back(); colas[cola_actual].pop_back();
            if (d!=dist[x]) continue;
            forn (i,g[x].size()) {
                int y=g[x][i].fst; ll c=g[x][i].snd;
                if (dist[y]<0||dist[x]+c<dist[y])
                    dist[y]=dist[x]+c,colas[(cola_actual+c)%K].pb({dist[y],y});
            }
        }
    }
}
// Uso: (peso de cualquier arista<=max_dist)
// kcolas(0,max_dist);