struct pt {
    tipo x, y;
    // tipo x, y, z; // only for 3d
    pt() {}
    pt(tipo _x, tipo _y) : x(_x), y(_y) {}
    // pt(tipo _x, tipo _y, tipo _z) : x(_x), y(_y), z(_z) {} // for 3d
    tipo norm2(){return *this**this;}
    tipo norm(){return sqrt(norm2());}
    pt operator+(pt o){return pt(x+o.x,y+o.y);}
    pt operator-(pt o){return pt(x-o.x,y-o.y);}
    pt operator*(tipo u){return pt(x*u,y*u);}
    pt operator/(tipo u) {
        if (u == 0) return pt(INF,INF);
        return pt(x/u,y/u);
    }
    tipo operator*(pt o){return x*o.x+y*o.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
    tipo operator^(pt o){return x*o.y-y*o.x;}
    tipo angle(pt o){return atan2(*this^o,*this*o);}
	pt unit(){return *this/norm();}
    bool left(pt p, pt q){ // is it to the left of directed line pq?
		return ((q-p)^(*this-p))>EPS;}
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
    bool collinear(pt p, pt q){return fabs((p-*this)^(q-*this))<EPS;}
    bool dir(pt p, pt q){ // does it have the same direction of pq?
        return this->collinear(p, q)&&(q-p)*(*this-p)>0;}
	pt rot(pt r){return pt(*this^r,*this*r);}
	pt rot(tipo a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);