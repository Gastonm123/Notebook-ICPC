// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<Pt> chull(vector<Pt> p){
	if(sz(p)<3)return p;
	vector<Pt> r;
	sort(p.begin(),p.end()); // first x, then y
	forr(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))
			r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))
			r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}