// https://open.kattis.com/problems/roberthood

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
tipo EPS=1e-9;

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
		return ((q-p)^(*this-p))>-EPS;}
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
    bool collinear(pt p, pt q){return fabs((p-*this)^(q-*this))<EPS;}
	pt rot(pt r){return pt(*this^r,*this*r);}
	pt rot(tipo a){return rot(pt(sin(a),cos(a)));}      
};

struct pol {
    int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
    tipo area() {
        ll a = 0;
        forr (i, 1, sz(p)-1) {
            a += (p[i]-p[0])^(p[i+1]-p[0]);
        }
        return abs(a)/2;
    }
    // bool has(pt q){ // O(n), winding number
	// 	forr(i,0,n)if(ln(p[i],p[(i+1)%n]).seghas(q))return true;
	// 	int cnt=0;
	// 	forr(i,0,n){
	// 		int j=(i+1)%n;
	// 		int k=sgn((q-p[j])^(p[i]-p[j]));
	// 		int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
	// 		if(k>0&&u<0&&v>=0)cnt++;
	// 		if(k<0&&v<0&&u>=0)cnt--;
	// 	}
	// 	return cnt!=0;
	// }
	void normalize(){ // (call before haslog, remove collinear first)
		if(p[2].left(p[0],p[1]))reverse(p.begin(),p.end());
		int pi=min_element(p.begin(),p.end())-p.begin();
		vector<pt> s(n);
		forr(i,0,n)s[i]=p[(pi+i)%n];
		p.swap(s);
	}
	bool haslog(pt q){ // O(log(n)) only CONVEX. Call normalize first
		if(q.left(p[0],p[1])||q.left(p.back(),p[0]))return false;
		int a=1,b=p.size()-1;  // returns true if point on boundary
		while(b-a>1){          // (change sign of EPS in left
			int c=(a+b)/2;       //  to return false in such case)
			if(!q.left(p[0],p[c]))a=c;
			else b=c;
		}
		return !q.left(p[a],p[a+1]);
	}
	bool isconvex(){//O(N), delete collinear points!
		if(n<3) return false;
		bool isLeft=p[0].left(p[1], p[2]);
		forr(i, 1, n)
			if(p[i].left(p[(i+1)%n], p[(i+2)%n])!=isLeft)
				return false;
		return true;
	}
	pt farthest(pt v){ // O(log(n)) only CONVEX
		if(n<10){
			int k=0;
			forr(i,1,n)if(v*(p[i]-p[k])>EPS)k=i;
			return p[k];
		}
		if(n==sz(p))p.pb(p[0]);
		pt a=p[1]-p[0];
		int s=0,e=n,ua=v*a>EPS;
		if(!ua&&v*(p[n-1]-p[0])<=EPS)return p[0];
		while(1){
			int m=(s+e)/2;pt c=p[m+1]-p[m];
			int uc=v*c>EPS;
			if(!uc&&v*(p[m-1]-p[m])<=EPS)return p[m];
			if(ua&&(!uc||v*(p[s]-p[m])>EPS))e=m;
			else if(ua||uc||v*(p[s]-p[m])>=-EPS)s=m,a=c,ua=uc;
			else e=m;
			assert(e>s+1);
		}
	}
	// pol cut(ln l){   // cut CONVEX polygon by line l
	// 	vector<pt> q;  // returns part at left of l.pq
	// 	forr(i,0,n){
	// 		int d0=sgn(l.pq^(p[i]-l.p)),d1=sgn(l.pq^(p[(i+1)%n]-l.p));
	// 		if(d0>=0)q.pb(p[i]);
	// 		ln m(p[i],p[(i+1)%n]);
	// 		if(d0*d1<0&&!(l/m))q.pb(l^m);
	// 	}
	// 	return pol(q);
	// }
	// tipo intercircle(circle c){ // area of intersection with circle
	// 	tipo r=0.;
	// 	forr(i,0,n){
	// 		int j=(i+1)%n;tipo w=c.intertriangle(p[i],p[j]);
	// 		if((p[j]-c.o)^(p[i]-c.o)>EPS)r+=w;
	// 		else r-=w;
	// 	}
	// 	return abs(r);
	// }
	tipo callipers(){ // square distance of most distant points
		tipo r=0;     // prereq: convex, ccw, NO COLLINEAR POINTS
		for(int i=0,j=n<2?0:1;i<j;++i){
			for(;;j=(j+1)%n){
				r=max(r,(p[i]-p[j]).norm2());
				if(((p[(i+1)%n]-p[i])^(p[(j+1)%n]-p[j]))<=EPS)break;
			}
		}
		return r;
	}
};

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	if(sz(p)<3)return p;
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	forr(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int c; cin >> c;
    vector<pt> ps(c); forn(i, c) cin >> ps[i].x >> ps[i].y;
    pol p(chull(ps));
    cout << fixed << setprecision(DECIMAL_DIG);
    cout << sqrt(p.callipers()) << endl;
}