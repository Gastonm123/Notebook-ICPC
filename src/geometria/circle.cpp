struct circle {
	pt o;tipo r;
	circle(pt o, tipo r):o(o),r(r){}
	circle(pt x, pt y, pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(pt p){return (o-p).norm()<=r+EPS;}
	vector<pt> operator^(circle c){ // ccw
		vector<pt> s;
		tipo d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		tipo x=(d*d-c.r*c.r+r*r)/(2*d);
		tipo y=sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		s.pb(o+v*x-v.rot(ccw90)*y);
		if(y>EPS)s.pb(o+v*x+v.rot(ccw90)*y);
		return s;
	}
	vector<pt> operator^(ln l){
		vector<pt> s;
		pt p=l.proj(o);
		tipo d=(p-o).norm();
		if(d-EPS>r)return s;
		if(abs(d-r)<=EPS){s.pb(p);return s;}
		d=sqrt(r*r-d*d);
		s.pb(p+l.pq.unit()*d);
		s.pb(p-l.pq.unit()*d);
		return s;
	}
	vector<pt> tang(pt p){
		tipo d=sqrt((p-o).norm2()-r*r);
		return *this^circle(p,d);
	}
	bool in(circle c){ // non strict
		tipo d=(o-c.o).norm();
		return d+r<=c.r+EPS;
	}
	tipo intertriangle(pt a, pt b){ // area of intersection with oab
		if(abs((o-a)%(o-b))<=EPS)return 0.;
		vector<pt> q={a},w=*this^ln(a,b);
		if(w.size()==2)for(auto p:w)if((a-p)*(b-p)<-EPS)q.pb(p);
		q.pb(b);
		if(q.size()==4&&(q[0]-q[1])*(q[2]-q[1])>EPS)swap(q[1],q[2]);
		tipo s=0;
		fore(i,0,q.size()-1){
			if(!has(q[i])||!has(q[i+1]))s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};