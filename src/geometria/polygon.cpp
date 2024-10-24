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
    bool has(pt q){ // O(n), winding number
		forr(i,0,n)if(ln(p[i],p[(i+1)%n]).seghas(q))return true;
		int cnt=0;
		forr(i,0,n){
			int j=(i+1)%n;
			int k=sgn((q-p[j])%(p[i]-p[j]));
			int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
			if(k>0&&u<0&&v>=0)cnt++;
			if(k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
	}
	void normalize(){ // (call before haslog, remove collinear first)
		if(p[2].left(p[0],p[1]))reverse(p.begin(),p.end());
		int pi=min_element(p.begin(),p.end())-p.begin();
		vector<pt> s(n);
		forr(i,0,n)s[i]=p[(pi+i)%n];
		p.swap(s);
	}
	bool haslog(pt q){ // O(log(n)) only CONVEX. Call normalize first
		if(q.left(p[0],p[1])||q.left(p.back(),p[0]))return false;
		int a=1,b=p.size()-1;  // returns true if point on boundary
		while(b-a>1){          // (change sign of EPS in left
			int c=(a+b)/2;       //  to return false in such case)
			if(!q.left(p[0],p[c]))a=c;
			else b=c;
		}
		return !q.left(p[a],p[a+1]);
	}
	bool isconvex(){//O(N), delete collinear points!
		int N=sz(p);
		if(N<3) return false;
		bool isLeft=p[0].left(p[1], p[2]);
		forr(i, 1, N)
			if(p[i].left(p[(i+1)%N], p[(i+2)%N])!=isLeft)
				return false;
		return true;
	}
};