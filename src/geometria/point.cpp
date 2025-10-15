using T = double;
bool iszero(T u) { return abs(u)<=EPS; }
struct Pt {
    T x, y;
    T z; // only for 3d
    Pt() {}
    Pt(T _x, T _y) : x(_x), y(_y) {}
    Pt(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {} // for 3d
    T norm2(){ return *this**this; }
    T norm(){ return sqrt(norm2()); }
    Pt operator+(Pt o){ return Pt(x+o.x,y+o.y); }
    Pt operator-(Pt o){ return Pt(x-o.x,y-o.y); }
    Pt operator*(T u){ return Pt(x*u,y*u); }
    Pt operator/(T u) {
        if (iszero(u)) return Pt(INF,INF);
        return Pt(x/u,y/u);
    }
    T operator*(Pt o){ return x*o.x+y*o.y; }
	Pt operator^(Pt p){ // only for 3D
		return Pt(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x); }
    T operator%(Pt o){ return x*o.y-y*o.x; }
    T angle(Pt o){ return atan2(*this%o, *this*o); }
//  T angle(Pt o){ // accurate around 90 degrees
//      if (*this%o>0) return acos(*this*o);
//      return 2*M_PI-acos(*this*o); }
	Pt unit(){ return *this/norm(); }
    bool left(Pt p, Pt q){ // is it to the left of directed line pq?
		return ((q-p)%(*this-p))>EPS; }
	bool operator<(Pt p)const{ // for convex hull
		return x<p.x-EPS||(iszero(x-p.x)&&y<p.y-EPS); }
    bool collinear(Pt p, Pt q){
        return iszero((p-*this)%(q-*this)); }
    bool dir(Pt p, Pt q){ // does it have the same direction of pq?
        return this->collinear(p, q)&&(q-p)*(*this-p)>EPS; }
	Pt rot(Pt r){ return Pt(*this%r,*this*r); }
	Pt rot(T a){ return rot(Pt(sin(a),cos(a))); }
};
Pt ccw90(1,0);
Pt cw90(-1,0);