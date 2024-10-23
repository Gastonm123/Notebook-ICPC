struct pol {
    int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
    double area() {
        ll a = 0;
        forr (i, 1, sz(p)-1) {
            a += (p[i]-p[0])^(p[i+1]-p[0]);
        }
        return abs(a)/2;
    }
};