// mínimo entero de f en (l,r)
ll ternary(auto f, ll l, ll r) {
    for (ll d = r-l; d > 2; d = r-l) {
        ll a = l+d/3, b = r-d/3;
        if (f(a) > f(b)) l = a; else r = b;
    }
    return l+1; // retorna un punto, no un resultado de evaluar f
}

// mínimo real de f en (l,r)
// para error < EPS, usar iters = log((r-l)/EPS)/log(1.618)
double golden(auto f, double l, double r, int iters) {
    constexpr double ratio = (3-sqrt(5))/2;
    double x1 = l+(r-l)*ratio, f1 = f(x1);
    double x2 = r-(r-l)*ratio, f2 = f(x2);
    while (iters--) {
        if (f1 > f2) l=x1, x1=x2, f1=f2, x2=r-(r-l)*ratio, f2=f(x2);
        else         r=x2, x2=x1, f2=f1, x1=l+(r-l)*ratio, f1=f(x1);
    }
    return (l+r)/2; // retorna un punto, no un resultado de evaluar f
}
