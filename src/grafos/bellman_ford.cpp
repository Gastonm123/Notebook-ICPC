const int INF=2e9; int n;
vector<pair<int,int> > g[MAXN]; // u->[(v,cost)]
ll dist[MAXN];
void bford(int src){ // O(nm)
	fill(dist,dist+n,INF);dist[src]=0;
	forr(_,0,n)forr(x,0,n)if(dist[x]!=INF)for(auto t:g[x]){
		dist[t.fst]=min(dist[t.fst],dist[x]+t.snd);
	}
	forr(x,0,n)if(dist[x]!=INF)for(auto t:g[x]){
		if(dist[t.fst]>dist[x]+t.snd){
			// neg cycle: all nodes reachable from t.fst have
            // -INF distance
			// to reconstruct neg cycle: save "prev" of each 
            // node, go up from t.fst until repeating a node.
            // this node and all nodes between the two
            // occurences form a neg cycle
		}
	}
}