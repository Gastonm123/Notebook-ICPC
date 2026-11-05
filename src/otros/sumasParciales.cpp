//PARTIAL SUMS 2D (creditos edu)
forr(i,1,n+1)forr(j,1,n+1)sp[i][j]=a[i-1][j-1]+sp[i][j-1];
forr(i,1,n+1)forr(j,1,n+1)sp[i][j]+=sp[i-1][j];

//IN K-DIMENSIONS
//store initial values
//for dimension d in range(k): for all elements mk in order:
//	sp[mk]+=sp[mk-1 en d] //anterior en dimension d
//example (k bit dimensions):
forn(mk,1ll<<k)sp[mk]=a[mk];
forn(d,k)forn(mk,1ll<<k){
	if(mk&(1ll<<d))sp[mk]+=sp[mk^(1ll<<d)];
}