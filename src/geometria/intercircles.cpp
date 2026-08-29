vector<double> intercircles(vector<circle> c){
	vector<double> r(SZ(c)+1); // r[k]: area covered by at least k circles
	fore(i,0,SZ(c)){
		int k=1;Cmp s(c[i].o);
		vector<pair<pt,int> > p={
			{c[i].o+pt(1,0)*c[i].r,0},
			{c[i].o-pt(1,0)*c[i].r,0}};
		fore(j,0,SZ(c))if(j!=i){
			bool b0=c[i].in(c[j]),b1=c[j].in(c[i]);
			if(b0&&(!b1||i<j))k++;
			else if(!b0&&!b1){
				auto v=c[i]^c[j];
				if(SZ(v)==2){
					p.pb({v[0],1});p.pb({v[1],-1});
					if(s(v[1],v[0]))k++;
				}
			}
		}
		sort(p.begin(),p.end(),
			[&](pair<pt,int> a, pair<pt,int> b){return s(a.fst,b.fst);});
		fore(j,0,SZ(p)){
			pt p0=p[j?j-1:SZ(p)-1].fst,p1=p[j].fst;
			double a=(p0-c[i].o).angle(p1-c[i].o);
			r[k]+=(p0.x-p1.x)*(p0.y+p1.y)/2+c[i].r*c[i].r*(a-sin(a))/2;
			k+=p[j].snd;
		}
	}
	return r;
}
