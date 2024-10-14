vector<int> g[MAXN];int n;
vector<int> tsort(){  // lexicographically smallest topological sort
	vector<int> r;priority_queue<int> q;
	vector<int> d(2*n,0);
	forn(i,n)forn(j,g[i].size())d[g[i][j]]++;
	forn(i,n)if(!d[i])q.push(-i);
	while(!q.empty()){
		int x=-q.top();q.pop();r.pb(x);
		forn(i,sz(g[x])){
			d[g[x][i]]--;
			if(!d[g[x][i]])q.push(-g[x][i]);
		}
	}
	return r;  // if not DAG it will have less than n elements
}