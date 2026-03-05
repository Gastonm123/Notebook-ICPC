// polygon intersecting left side of halfplanes
struct Halfplane:public Ln{
	double angle;
	Halfplane(){}
	Halfplane(Pt a,Pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(Halfplane b)const{return angle<b.angle;}
	bool out(Pt q){return pq%(q-p)<-EPS;}
};
vector<Pt> intersect(vector<Halfplane> b){
	vector<Pt>bx={{DINF,DINF},{-DINF,DINF},
				  {-DINF,-DINF},{DINF,-DINF}};
	forr(i,0,4) b.pb(Halfplane(bx[i],bx[(i+1)%4]));
	sort(all(b));
	int n=sz(b),q=1,h=0;
	vector<Halfplane> c(sz(b)+10);
	forn(i,0,n){
		while(q<h&&b[i].out(c[h]^c[h-1])) h--;
		while(q<h&&b[i].out(c[q]^c[q+1])) q++;
		c[++h]=b[i];
		if(q<h&&abs(c[h].pq%c[h-1].pq)<EPS){
			if(c[h].pq*c[h-1].pq<=0) return {};
			h--;
			if(b[i].out(c[h].p)) c[h]=b[i];
		}
	}
	while(q<h-1&&c[q].out(c[h]^c[h-1]))h--;
	while(q<h-1&&c[h].out(c[q]^c[q+1]))q++;
	if(h-q<=1)return {};
	c[h+1]=c[q];
	vector<Pt> s;
	forr(i,q,h+1) s.pb(c[i]^c[i+1]);
	return s;
}