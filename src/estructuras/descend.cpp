// Descenso por un segment tree. Devuelve la primer posicion que cumple la condicion
// Agregar al struct de RMQ
int descend(int i, int j, int n, int a, int b) {
    if (j<=a || i>=b) return -1;
    if (n>=sz) return COND() ? n-sz : -1;
    int c=(a+b)/2;
    if (i<=a && b<=j) {
        if (IR_IZQ())
            return descend(i,j,2*n,a,c);
        else
            return descend(i,j,2*n+1,c,b);
    }
    int res=descend(i,j,2*n,a,c);
    if (res!=-1) return res;
    res=descend(i,j,2*n+1,c,b);
    return res;
}
int descend(int i, int j) {return descend(i,j,1,0,sz);}