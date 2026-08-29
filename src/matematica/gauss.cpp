double reduce(vector<vector<double>> &a){  //Devuelve determinante si m == n
	int m=sz(a), n=sz(a[0]), f=0, c=0; double r = 1.0;
	while(f < m and c < n){
		int h = f;
		// buscar fila con el mayor valor — menor inestabilidad numerica
		forr(k, f+1, m) if(abs(a[k][c]) > abs(a[h][c])) h = k;
		// mayor igual a cero — pasar de columna
		if(abs(a[h][c]) < EPS){ c++; r=0.0; continue; }
		// intercambiar filas
		if(h != f){ r = -r; swap(a[f], a[h]); }
		r *= a[f][c];
		// normalizar la fila
		dforr(k, c, n) a[f][k] /= a[f][c];
		forr(k, 0, m) if(k != f) {
			// restar filas arriba y abajo
			dforr(l_, c, n) a[k][l_] -= a[k][c] * a[f][l_];
		}
		f++; c++;
	}
	return r;
}
vector<int> reduce2(vector<bitset<MAXN>> &a) {
	vector<int> pivots;
	forn (i, sz(a)) {
		for (int p : pivots) a[i]=min(a[i],a[i]^a[p]);
		if (a[i].any()) {
			// restar fila a los pivots
			for (int p : pivots) a[p]=min(a[p],a[p]^a[i]);
			// insertar manteniendo el orden
			forn (j, sz(pivots)+1)
				if (j==sz(pivots) || a[i]>a[pivots[j]]) 
					pivots.insert(pivots.begin()+j,i);
		}
	}
	return pivots;
}