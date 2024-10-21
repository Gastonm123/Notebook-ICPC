// normalizar los poligonos antes de hacer la suma
// si son poligonos concavos llamar a chull luego y normalizar
// si son convexos eliminar puntos colineales y normalizar
vector<pt> minkowski_sum(vector<pt> p, vector<pt> q){
	int n=sz(p),m=sz(q),x=0,y=0;
	forr(i,0,n) if(p[i]<p[x]) x=i;
	forr(i,0,m) if(q[i]<q[y]) y=i;
	vector<pt> ans={p[x]+q[y]};
	forr(it,1,n+m){
		pt a=p[(x+1)%n]+q[y];
		pt b=p[x]+q[(y+1)%m];
		if(b.left(ans.back(),a)) ans.pb(b), y=(y+1)%m;
		else ans.pb(a), x=(x+1)%n;
	}
	return ans; }