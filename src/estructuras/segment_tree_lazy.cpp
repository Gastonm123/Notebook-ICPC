//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
//Segtree de reemplazo en rango y suma en rango
typedef int Elem;//Elem de los elementos del arreglo
typedef int Alt;//Elem de la alteracion
#define oper(x,y) (x+y)
const Elem neutro=0; const Alt neutro2=-1;
struct RMQ{
	int sz;
	Elem t[4*MAXN];
	Alt dirty[4*MAXN];//las alteraciones pueden ser distintas a Elem
	Elem &operator[](int p){return t[sz+p];}
	void init(int n){//O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forn(i, 2*sz) t[i]=neutro;
		forn(i, 2*sz) dirty[i]=neutro2;
	}
	void updall(){dforn(i, sz) t[i]=oper(t[2*i], t[2*i+1]);} // O(N)
	void push(int n, int a, int b){//propaga el dirty a sus hijos
		if(dirty[n]!=neutro2){
			if(n<sz){
				t[2*n] = (b-a)/2*dirty[n];
				t[2*n+1] = (b-a)/2*dirty[n];
				dirty[2*n] = dirty[n];
				dirty[2*n+1] = dirty[n];
			}
			dirty[n]=neutro2;
		}
	}
	Elem get(int i, int j, int n, int a, int b){//O(lgn)
		push(n, a, b);
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return oper(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	Elem get(int i, int j){return get(i,j,1,0,sz);}
	//altera los valores en [i, j) con una alteracion de val
	void alterar(Alt val,int i,int j,int n,int a,int b){//O(lgn)
		push(n, a, b);
		if(j<=a || i>=b) return;
		if(i<=a && b<=j){
			t[n] = (b-a)*val;
			dirty[n] = val;
			return;
		}
		int c=(a+b)/2;
		alterar(val, i, j, 2*n, a, c);
		alterar(val, i, j, 2*n+1, c, b);
		t[n]=oper(t[2*n], t[2*n+1]);
	}
	void alterar(Alt val, int i, int j){alterar(val,i,j,1,0,sz);}
} rmq;