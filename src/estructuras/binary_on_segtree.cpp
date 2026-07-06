// Busqueda binaria en un mergesort tree`
#define includes(bolsa,t) (bolsa.count(t))
typedef int Val;
int search_first(RMQ &rmq, Val v, int i, int j, int n, int a, int b) {
    if (j<=a || i>=b) return -1;
    if (n>=rmq.sz) return includes(rmq.t[n],v) ? n-rmq.sz : -1;
    int c=(a+b)/2;
    if (i<=a && b<=j) {
        if (includes(rmq.t[2*n],v))
            return search_first(rmq,v,i,j,2*n,a,c);
        else
            return search_first(rmq,v,i,j,2*n+1,c,b);
    }
    int res=search_first(rmq,v,i,j,2*n,a,c);
    if (res!=-1) return res;
    res=search_first(rmq,v,i,j,2*n+1,c,b);
    return res;
}
int search_first(RMQ &rmq, Val v, int i, int j) {return search_first(rmq,v,i,j,1,0,rmq.sz);}