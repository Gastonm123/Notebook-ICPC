ll STR[MAXN][MAXN], Bell[MAXN];
//STR[n][k] = formas de particionar un conjunto de n elementos en k conjuntos
//Bell[n] = formas de particionar un conjunto de n elementos
forr(i, 1, MAXN)STR[i][1] = 1;
forr(i, 2, MAXN)STR[1][i] = 0;
forr(i, 2, MAXN)forr(j, 2, MAXN){
    STR[i][j] = (STR[i-1][j-1] + j*STR[i-1][j]%MOD) %MOD;  
}
forn(i, MAXN){
    Bell[i] = 0;
    forn(j, MAXN){
        Bell[i] = (Bell[i] + STR[i][j]) %MOD;
    }
}
