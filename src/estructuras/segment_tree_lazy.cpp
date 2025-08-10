//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
typedef int Elem;//Elem de los elementos del arreglo
typedef int Alt;//Elem de la alteracion
#define oper(x,y) x+y
#define oper2(k,a,b) k*(b-a)//Aplicar actualizacion sobre [a, b)
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
	void push(int n, int a, int b){//propaga el dirty a sus hijos
		if(dirty[n]!=0){
			t[n]+=oper2(dirty[n], a, b);//altera el nodo 
			if(n<sz){//cambiar segun el problema
				dirty[2*n]   = dirty[n];
				dirty[2*n+1] = dirty[n];
			}
			dirty[n]=0;
		}
	}
	Elem get(int i, int j, int n, int a, int b){//O(lgn)
		if(j<=a || i>=b) return neutro;
		push(n, a, b);
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
			dirty[n]+=val;
			push(n, a, b);
			return;
		}
		int c=(a+b)/2;
		alterar(val, i, j, 2*n, a, c);
		alterar(val, i, j, 2*n+1, c, b);
		t[n]=oper(t[2*n], t[2*n+1]);
	}
	void alterar(Alt val, int i, int j){alterar(val,i,j,1,0,sz);}
}rmq;