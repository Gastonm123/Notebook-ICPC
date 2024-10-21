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
    pt operator*(ll c) {return {c*x, c*y};}
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

// normalizar los poligonos antes de hacer la suma
// si son poligonos concavos llamar a chull luego y normalizar
// si son convexos eliminar puntos colineales y normalizar
vector<pt> minkowski_sum(vector<pt> p, vector<pt> q){
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
	return ans; }

vector<pt> polish(vector<pt> p) {
    vector<pt> r; r.pb(p[0]);
    forr (i, 1, sz(p)) if(!collinear(r.back(), p[i], p[(i+1)%sz(p)])) r.pb(p[i]);
    normalize(r);
    return r;
}

int main(int argc, char **argv){ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if(argc == 2) freopen(argv[1], "r", stdin);
    
    vector<pt> polys[2];
    int ms[2];
    forn (i, 2) {
        cin >> ms[i]; polys[i].resize(ms[i]);
        forn (j, ms[i]) {
            cin >> polys[i][j].x >> polys[i][j].y;
        }
        normalize(polys[i]);
    }

    int n; cin >> n; vector<pt> puntos(n);
    forn (i, n) {
        cin >> puntos[i].x >> puntos[i].y;
    }

    vector<bool> posible(n, 0);
    vector<pt> p1 = polys[0], p2 = polys[1], mink[3];
    mink[0] = polish(minkowski_sum(p1, p2));
    forn (i, n) {
        posible[i] = haslog(puntos[i]*2, mink[0]);
    }

    // de p1 a p2
    forn (i, sz(p1)) p1[i] = polys[0][i]*(-1);
    forn (i, sz(p2)) p2[i] = polys[1][i]*2;
    mink[1]  = polish(minkowski_sum(p1, p2));
    forn (i, n) {
        posible[i] = posible[i] || haslog(puntos[i], mink[1]);
    }

    // de p2 a p1
    forn (i, sz(p1)) p1[i] = polys[0][i]*2;
    forn (i, sz(p2)) p2[i] = polys[1][i]*(-1);
    mink[2]  = polish(minkowski_sum(p1, p2));
    forn (i, n) {
        posible[i] = posible[i] || haslog(puntos[i], mink[2]);
    }

    forn (i, n) {
        cout << (posible[i] ? "Y" : "N");
    } cout << endl;
    return 0;
}