// Dado un array y una operacion asociativa con neutro, get(i,j) opera en [i,j)
#define MAXN 100000
#define oper(x, y) max(x, y)
const int neutro=0;
struct RMQ{
	int sz;
	tipo t[4*MAXN];
	tipo &operator[](int p){return t[sz+p];}
	void init(int n){ // O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forn(i, 2*sz) t[i]=neutro;
	}
	void updall(){dforn(i, sz) t[i]=oper(t[2*i], t[2*i+1]);} // O(N)
	tipo get(int i, int j){return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b){ // O(lgn)
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return oper(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	void set(int p, tipo val){ // O(lgn)
		for(p+=sz; p>0 && t[p]!=val;){
			t[p]=val;
			p/=2;
			val=oper(t[p*2], t[p*2+1]);
		}
	}
}rmq;
// Usage:
cin >> n; rmq.init(n); forn(i, n) cin >> rmq[i]; rmq.updall();