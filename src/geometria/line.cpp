int sgn2(tipo x){return x<0?-1:1;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return dist(r)<=EPS;}
	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))<=EPS;}
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<=EPS;} // 3D
	bool operator/(ln l){return abs(pq.unit()^l.pq.unit())<=EPS;} // 2D
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection
		if(*this/l)return pt(INF,INF);
        tipo a=-pq.y, b=pq.x, c=p.x*a+p.y*b;
        tipo la=-l.pq.y, lb=l.pq.x, lc=l.p.x*la+l.p.y*lb;
        tipo det = a * lb - b * la;
        pt r((lb*c-b*lc)/det, (a*lc-c*la)/det);
        return r;
//		pt r=l.p+l.pq*(((p-l.p)^pq)/(l.pq^pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
	}
	tipo angle(ln l){return pq.angle(l.pq);}
	int side(pt r){return has(r)?0:sgn2(pq^(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt segclosest(pt r) {
	   tipo l2 = pq.norm2();
	   if(l2==0.) return p;
	   tipo t =((r-p)*pq)/l2;
	   return p+(pq*min(1,max(0,t)));
	}
	pt ref(pt r){return proj(r)*2-r;}
	tipo dist(pt r){return (r-proj(r)).norm();}
//	tipo dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){ // angle bisector
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}
ln bisector(pt p, pt q){ // segment bisector (2D)
	return ln((p+q)*.5,p).rot(ccw90);
}
