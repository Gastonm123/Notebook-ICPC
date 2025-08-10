#define oper min
Elem st[K][1<<K]; // K tal que (1<<K) > n
void st_init(vector<Elem>& a) {
    int n = sz(a); // assert(K >= 31-__builtin_clz(2*n));
    forn(i,n) st[0][i] = a[i];
    forr(k,1,K) forn(i,n-(1<<k)+1)
        st[k][i] = oper(st[k-1][i], st[k-1][i+(1<<(k-1))]);
}
Elem st_query(int l, int r) { // assert(l<r);
    int k = 31-__builtin_clz(r-l);
    return oper(st[k][l], st[k][r-(1<<k)]);
}
// si la operacion no es idempotente
Elem st_query(int l, int r) {
    int k = 31-__builtin_clz(r-l);
    Elem res = st[k][l];
    for (l+=(1<<k), k--; l<r; k--) {
        if (l+(1<<k)<=r) {
            res = oper(res, st[k][l]);
            l += (1<<k);
        }
    }
    return res;
}
