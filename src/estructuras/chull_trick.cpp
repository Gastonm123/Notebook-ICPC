typedef ll tc;
struct Line{tc m,h;};
struct CHT { // for minimum (for maximum just change the sign of lines)
	vector<Line> c;
	int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0); // ==ceil(x/y)
	}
	void add(tc m, tc h){ // m's should be non increasing
		Line l=(Line){m,h};
		if(sz(c)&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(sz(c)>1&&in(c.back(),l)<=in(c[sz(c)-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.pb(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	tc eval(tc x){
		// O(log n) query:
		int s=0,e=c.size();
		while(e-s>1){int m=(s+e)/2;
			if(fbin(x,m-1))e=m;
			else s=m;
		}
		return c[s].m*x+c[s].h;
		// O(1) query (for ordered x's):
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

struct line { int a, b; }; // y = ax + b
vector<line> cht(vector<line> a) {
	sort(all(a), [](line x, line y) {
		return make_pair(x.a, x.b) < make_pair(y.a, y.b); });
	vector<line> b = {a[0]};
	forr(i, 1, sz(a)) { line z = a[i];
		if (b.back().a == z.a) b.pop_back();
		while (sz(b) >= 2) { line x = b[sz(b)-2], y = b[sz(b)-1];
			if (ll(x.b-y.b)*(z.a-x.a) < ll(x.b-z.b)*(y.a-x.a)) break;
			b.pop_back();
		}
		b.pb(z);
	}
	return b;
}