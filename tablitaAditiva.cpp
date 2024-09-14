// Tablita aditiva 2D
forn (dim, 2) {
    forn (i, N) {
        forn (j, M) {
            int pi = i-(dim==0), pj = j-(dim==1);
            if (pi >= 0 && pj >= 0) {
                dp[i][j] += dp[pi][pj];
            }
        }
    }
}
// Generalizacion a 32 dimensiones para mascaras de bits
forn (i, 32) {
    forn (mask, 1<<32) {
        if ((mask>>i)&1) {
            dp[mask] += dp[mask - (1<<i)];
        }
    }
}