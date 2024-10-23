// https://codeforces.com/gym/105321/problem/C
// no se usa mucho el punto.. podria mejorarse

#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cout << #v "=" << v << endl //;)
#define forr(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) forr(i, 0, n)
#define dforn(i, n) for (int i = n - 1; i >= 0; i--)
#define forall(it, v) for (auto it = v.begin(); it != v.end(); ++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
#define mid(a,b) ((a+b)>>1)
#define all(v) begin(v),end(v)
#define mp make_pair
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long double tipo;

tipo INF=1e100;
tipo EPS=1e-13;
struct pt {
    // tipo x, y;
    tipo x, y, z; // only for 3d
    pt() {}
    pt(tipo _x, tipo _y) : x(_x), y(_y) {}
    pt(tipo _x, tipo _y, tipo _z) : x(_x), y(_y), z(_z) {} // for 3d
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
	pt rot(pt r){return pt(*this^r,*this*r);}
	pt rot(tipo a){return rot(pt(sin(a),cos(a)));}      
};

const tipo PI=4*atanl(1.0);

int main(int argc, char **argv){ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if(argc == 2) freopen(argv[1], "r", stdin);
    
    int n; cin >> n; pt c, s;
    cin >> c.x >> c.y >> c.z >> s.x >> s.y >> s.z;

    vector<pt> base(n);
    forn (i, n) {
        cin >> base[i].x >> base[i].y;
    }

    pt z(s.x+(c.x-s.x)/(s.z-c.z)*s.z, s.y+(c.y-s.y)/(s.z-c.z)*s.z);

    tipo angle = 0;
    bool ccw = 0, parteBase = 0; int cual;
    forn (i, n) {
        if (base[i].x == z.x && base[i].y == z.y) { parteBase = 1; cual = i; break; }
        tipo delta = (base[i]-z).angle(base[i<n-1?i+1:0]-z);
        if (delta > EPS) ccw = 1; angle += delta;
    }
    if (parteBase) {
        ccw = 0;
        forn (i, n) {
            if (i != cual && (i<n-1?i+1:0) != cual) {
                tipo delta = (base[i]-z).angle(base[i<n-1?i+1:0]-z);
                if (delta > EPS) ccw = 1;
            }
        }
        if (ccw) { cout << "S" << endl; }
        else { cout << "N" << endl; }
    }
    else if (fabs(fabs(angle) - 2*PI) > EPS || ccw) { cout << "S" << endl; }
    else { cout << "N" << endl; }

    return 0;
}