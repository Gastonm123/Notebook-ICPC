struct Fenwick{
    ll t[N]={};
    void adjust(int p, ll v){
        for(int i=p+1;i<N;i+=(i&-i)) t[i]+=v;
    }
    ll sum(int p){ // suma [0,p)
        ll s = 0;
        for(int i=p;i;i-=(i&-i)) s+=t[i];
        return s;
    }
    ll sum(int a, int b){return sum(b)-sum(a);} // suma [a,b)

    // funciona solo con valores no negativos en el fenwick
    // pref(v) devuelve el primer entero p con suma [0,p) >= v.
    // similar a lower_bound. si no existe devuelve N
    int pref(ll v){
        ll x = 0;
        for (int d=1<<30;d;d>>=1){
            if(x+d<N && t[x+d]<v) x+=d, v-=t[x];
        }
        return x+1;
    }
};

struct RangeFT { // 0-indexed, query [0, i), update [l, r)
	Fenwick rate, err;
	void adjust(int l, int r, int x) { // range update
		rate.adjust(l, x); rate.adjust(r, -x); 
        err.adjust(l, -x*l); err.adjust(r, x*r); 
    }
	ll sum(int i) { return rate.sum(i) * i + err.sum(i); }
}; // prefix query


struct Fenwick2D{
    ll t[N][M]={};
    void adjust(int p, int q, ll v){
        for(int i=p+1;i<N;i+=(i&-i)) 
            for(int j= q+1; j<M; j+=(j&-j))
                t[i][j]+=v;
    }
    ll sum(int p,int q){ // suma [0,p)
        ll s = 0;
        for(int i=p;i;i-=(i&-i)) 
            for(int j=q; j; j-=(j&-j))
                s+=t[i][j];
        return s;
    }
    ll sum(int x1, int y1, int x2, int y2){
        return sum(x2,y2)-sum(x1,y2)-sum(x2,y1)+sum(x1,y1);
    } // suma [a,b)
};




