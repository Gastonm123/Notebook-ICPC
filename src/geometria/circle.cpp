using T = double;
struct Circle {
	Pt o;T r;
	Circle(Pt o, T r):o(o),r(r){}
	Circle(Pt x, Pt y, Pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(Pt p){return (o-p).norm()<=r+EPS;}
	vector<Pt> operator^(Circle c){ // ccw
		vector<Pt> s;
		T d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		T x=(d*d-c.r*c.r+r*r)/(2*d);
		T y=sqrt(r*r-x*x);
		Pt v=(c.o-o)/d;
		s.pb(o+v*x-v.rot(ccw90)*y);
		if(y>EPS)s.pb(o+v*x+v.rot(ccw90)*y);
		return s;
	}
	vector<Pt> operator^(Ln l){
		vector<Pt> s;
		Pt p=l.proj(o);
		T d=(p-o).norm();
		if(d-EPS>r)return s;
		if(abs(d-r)<=EPS){s.pb(p);return s;}
		d=sqrt(r*r-d*d);
		s.pb(p+l.pq.unit()*d);
		s.pb(p-l.pq.unit()*d);
		return s;
	}
	vector<Pt> tang(Pt p){
		T d=sqrt((p-o).norm2()-r*r);
		return *this^Circle(p,d);
	}
	bool in(Circle c){ // non strict
		T d=(o-c.o).norm();
		return d+r<=c.r+EPS;
	}
	T intertriangle(Pt a, Pt b){ // area of intersection with oab
		if(abs((o-a)%(o-b))<=EPS)return 0.;
		vector<Pt> q={a},w=*this^Ln(a,b);
		if(w.size()==2)for(auto p:w)if((a-p)*(b-p)<-EPS)q.pb(p);
		q.pb(b);
		if(q.size()==4&&(q[0]-q[1])*(q[2]-q[1])>EPS)
			swap(q[1],q[2]);
		T s=0;
		fore(i,0,q.size()-1){
			if(!has(q[i])||!has(q[i+1]))
				s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};