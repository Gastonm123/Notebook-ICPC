#define oper min
int st[K][1<<K];int n;  // K such that 2^K>n
void st_init(vector<int> a){
	forn(i,n)st[0][i]=a[i];
	forr(k,1,K)forn(i,n-(1<<k)+1)
		st[k][i]=oper(st[k-1][i],st[k-1][i+(1<<(k-1))]);
}
int st_query(int s, int e){
	int k=31-__builtin_clz(e-s);
	return oper(st[k][s],st[k][e-(1<<k)]);
}