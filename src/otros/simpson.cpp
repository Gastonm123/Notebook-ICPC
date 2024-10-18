// integra f en [a,b] llamándola 2*n veces
double simpson(auto f, double a, double b, int n=1e4) {
    double h = (b-a)/2/n, s = f(a);
    forr(i,1,2*n) s += f(a+i*h) * ((i%2)?4:2);
    return (s+f(b))*h/3;
}
