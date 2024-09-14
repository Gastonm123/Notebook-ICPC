struct Fenwick {
    static const int sz = 1<<11;
    ll t[sz];
    void adjust(ll v, int p) {
        for (int i=p; i<sz; i+=(i&-i)) t[i]+=v;  }
    ll sum(int p){
        ll s=0;
        for(int i=p; i; i-=(i&-i)) s+=t[i];
        return s;
    }
    ll sum(int a, int b) {return sum(b)-sum(a-1);}
};

struct RangeFenwick {
    Fenwick add;
    Fenwick sub;
    void adjust(ll v, int a, int b) {
        add.adjust(v,a);
        add.adjust(-v,b+1);
        sub.adjust((a-1)*v,a);
        sub.adjust(-b*v,b+1);
    }
    ll sum(int p) {
        return 1ll * p * add.sum(p) - sub.sum(p);
    }
    ll sum(int a, int b) {
        return sum(b) - sum(a-1);
    }
};

struct Fenwick2D {
    static const int sz=(1<<10);
    Fenwick t[sz];
    void adjust(int x, int y, ll v) {
        for (int i=x; i<sz; i+=(i&-i)) t[i].adjust(y,v);}
    ll sum(int x, int y) {
        ll s=0;
        for (int i=x; i; i-=(i&-i)) s += t[i].sum(y);
        return s;
    }
    ll sum(int x1, int y1, int x2, int y2) {
        ll s = sum(x2,y2)
             + ((x1>1) ? -sum(x1-1,y2) : 0)
             + ((y1>1) ? -sum(x2,y1-1) : 0)
             + ((x1>1&&y1>1) ? sum(x1-1,y1-1) : 0);
        return s;
    }
};