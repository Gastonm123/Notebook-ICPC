bool iszero(td u) { return abs(u)<=EPS; }
struct pt {
    td x, y;
    td z; // only for 3d
    pt() {}
    pt(td _x, td _y) : x(_x), y(_y) {}
    pt(td _x, td _y, td _z) : x(_x), y(_y), z(_z) {} // for 3d
    td norm2(){ return *this**this; }
    td norm(){ return sqrt(norm2()); }
    pt operator+(pt o){ return pt(x+o.x,y+o.y); }
    pt operator-(pt o){ return pt(x-o.x,y-o.y); }
    pt operator*(td u){ return pt(x*u,y*u); }
    pt operator/(td u) {
        if (iszero(u)) return pt(INF,INF);
        return pt(x/u,y/u);
    }
    td operator*(pt o){ return x*o.x+y*o.y; }
	pt operator^(pt p){ // only for 3D
		return pt(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x); }
    td operator%(pt o){ return x*o.y-y*o.x; }
    td angle(pt o){ return atan2(*this%o, *this*o); }
	pt unit(){ return *this/norm(); }
    bool left(pt p, pt q){ // is it to the left of directed line pq?
		return ((q-p)%(*this-p))>EPS; }
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(iszero(x-p.x)&&y<p.y-EPS); }
    bool collinear(pt p, pt q){
        return iszero((p-*this)%(q-*this)); }
    bool dir(pt p, pt q){ // does it have the same direction of pq?
        return this->collinear(p, q)&&(q-p)*(*this-p)>EPS; }
	pt rot(pt r){ return pt(*this%r,*this*r); }
	pt rot(td a){ return rot(pt(sin(a),cos(a))); }
};
pt ccw90(1,0);
pt cw90(-1,0);