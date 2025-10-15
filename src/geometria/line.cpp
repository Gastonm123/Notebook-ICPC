using T = double;
int sgn2(T x){return x<0?-1:1;}
struct Ln {
	Pt p,pq;
	Ln(Pt p, Pt q):p(p),pq(q-p){}
	Ln(){}
	bool has(Pt r){return dist(r)<=EPS;}
	bool seghas(Pt r){return has(r)&&(r-p)*(r-(p+pq))<=EPS;}
//	bool operator /(Ln l){return (pq.unit()^l.pq.unit()).norm()<=EPS;} // 3D
	bool operator/(Ln l){return abs(pq.unit()^l.pq.unit())<=EPS;} // 2D
	bool operator==(Ln l){return *this/l&&has(l.p);}
	Pt operator^(Ln l){ // intersection
		if(*this/l)return Pt(INF,INF);
        T a=-pq.y, b=pq.x, c=p.x*a+p.y*b;
        T la=-l.pq.y, lb=l.pq.x, lc=l.p.x*la+l.p.y*lb;
        T det = a * lb - b * la;
        Pt r((lb*c-b*lc)/det, (a*lc-c*la)/det);
        return r;
//		Pt r=l.p+l.pq*(((p-l.p)^pq)/(l.pq^pq));
//		if(!has(r)){return Pt(NAN,NAN,NAN);} // check only for 3D
	}
	T angle(Ln l){return pq.angle(l.pq);}
	int side(Pt r){return has(r)?0:sgn2(pq^(r-p));} // 2D
	Pt proj(Pt r){return p+pq*((r-p)*pq/pq.norm2());}
	Pt segclosest(Pt r) {
	   T l2 = pq.norm2();
	   if(l2==0.) return p;
	   T t =((r-p)*pq)/l2;
	   return p+(pq*min(1,max(0,t)));
	}
	Pt ref(Pt r){return proj(r)*2-r;}
	T dist(Pt r){return (r-proj(r)).norm();}
//	T dist(Ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
	Ln rot(auto a){return Ln(p,p+pq.rot(a));} // 2D
};
Ln bisector(Ln l, Ln m){ // angle bisector
	Pt p=l^m;
	return Ln(p,p+l.pq.unit()+m.pq.unit());
}
Ln bisector(Pt p, Pt q){ // segment bisector (2D)
	return Ln((p+q)*.5,p).rot(ccw90);
}
