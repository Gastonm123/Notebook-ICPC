// https://codeforces.com/gym/104252/problem/G

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

struct pt {
    ll x, y;
    pt operator-(pt p) {return {x-p.x,y-p.y};}
    pt operator+(pt p) {return {x+p.x,y+p.y};}
    pt operator*(ll c)  const{return {c*x, c*y};}
    pt operator*(int c) const{return {c*x, c*y};}
    pt operator/(ll c) {return {x/c, y/c};}
    ll operator^(pt p) {return x*p.y-y*p.x;}
    bool operator==(pt p) {return mp(x,y) == mp(p.x,p.y);}
    bool operator<(pt p) {return mp(x,y) < mp(p.x,p.y);}
    bool left(pt p, pt q) { // it it to the left or onto the directed line pq?
        return ((q-p)^(*this-p)) >= 0; }
    bool left2(pt p, pt q) { // it it to the left of directed line pq?
        return ((q-p)^(*this-p)) > 0; }
};

bool collinear (pt &p, pt &q, pt &r) {
    return abs((p-q) ^ (r-q)) == 0;
}

void normalize(vector<pt> &p) {
    if(p[2].left2(p[0],p[1])) reverse(p.begin(), p.end());
    int pi = min_element(all(p))-p.begin();
    vector<pt> s(sz(p));
    forr(i,0,sz(p))s[i]=p[(pi+i)%(sz(p))];
    p.swap(s);
}

bool haslog(pt q, vector<pt> &p) {
    if(q.left2(p[0],p[1])||q.left2(p.back(),p[0]))return false;
    int a=1, b=p.size()-1;
    while (b-a>1) {
        int c=(a+b)/2;
        if(!q.left2(p[0],p[c]))a=c;
        else b=c;
    }
    return !q.left2(p[a],p[a+1]);
}

// CCW order
// Does not include collinear points (change left for left2 to include)
vector<pt> chull(vector<pt> &p){
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

using td = int;
vector<pt> operator*(const vector<pt> &p, td u) {
    vector<pt> r;
    forn (i, sz(p)) r.pb(p[i]*u);
    return r;
}
vector<pt> minkowski_sum(vector<pt> &p, vector<pt> &q){
	int n=sz(p),m=sz(q),x=0,y=0;
	forr(i,0,n) if(p[i]<p[x]) x=i;
	forr(i,0,m) if(q[i]<q[y]) y=i;
	vector<pt> ans={p[x]+q[y]};
	forr(it,1,n+m){
		pt a=p[(x+1)%n]+q[y];
		pt b=p[x]+q[(y+1)%m];
		if(b.left(ans.back(),a)) ans.pb(b), y=(y+1)%m;
		else ans.pb(a), x=(x+1)%n;
	}
	return ans;
}
vector<pt> do_minkowski(vector<pt> &p, vector<pt> &q) {
    normalize(p); normalize(q);
    vector<pt> sum = minkowski_sum(p, q);
	return chull(sum); // no normalizado
}

int main(int argc, char **argv){ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if(argc == 2) freopen(argv[1], "r", stdin);
    
    vector<pt> polys[2];
    forn (i, 2) {
        int n; cin >> n;
        polys[i].resize(n);
        forn (j, n) {
            cin >> polys[i][j].x >> polys[i][j].y;
        }
    }

    int n; cin >> n; vector<pt> puntos(n);
    forn (i, n) {
        cin >> puntos[i].x >> puntos[i].y;
    }

    vector<bool> posible(n, 0);
    vector<pt> mink, p1, p2;
    mink = do_minkowski(polys[0], polys[1]);
    normalize(mink);
    forn (i, n) {
        posible[i] = haslog(puntos[i]*2, mink);
    }
    
    // de p1 a p2
    p1 = polys[0] * -1;
    p2 = polys[1] * 2;
    mink = do_minkowski(p1, p2);
    normalize(mink);
    forn (i, n) {
        posible[i] = posible[i] || haslog(puntos[i], mink);
    }
    
    // de p2 a p1
    p1 = polys[0] * 2;
    p2 = polys[1] * -1; 
    mink = do_minkowski(p1, p2);
    normalize(mink);
    forn (i, n) {
        posible[i] = posible[i] || haslog(puntos[i], mink);
    }

    forn (i, n) {
        cout << (posible[i] ? "Y" : "N");
    } cout << endl;
    return 0;
}