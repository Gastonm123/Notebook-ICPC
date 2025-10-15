vector<Pt> minkowski_sum(vector<Pt> &p, vector<Pt> &q){
	int n=sz(p),m=sz(q),x=0,y=0;
	forr(i,0,n) if(p[i]<p[x]) x=i;
	forr(i,0,m) if(q[i]<q[y]) y=i;
	vector<Pt> ans={p[x]+q[y]};
	forr(it,1,n+m){
		Pt a=p[(x+1)%n]+q[y];
		Pt b=p[x]+q[(y+1)%m];
		if(b.left(ans.back(),a)) ans.pb(b), y=(y+1)%m;
		else ans.pb(a), x=(x+1)%n;
	}
	return ans;
}
vector<Pt> do_minkowski(vector<Pt> &p, vector<Pt> &q) {
	normalize(p); normalize(q);
	vector<Pt> sum = minkowski_sum(p, q);
	return chull(sum); // no normalizado
}
// escalar poligono
vector<Pt> operator*(vector<Pt> &p, td u) {
    vector<Pt> r; forn (i, sz(p)) r.pb(p[i]*u);
    return r;
}