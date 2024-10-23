// subsecuencia creciente más larga
// para no decreciente, borrar la línea 9 con el continue
template<class Type> vector<int> lis(vector<Type>& a) {
    int n = sz(a);
    vector<int> seq, prev(n,-1), idx(n+1,-1);
    vector<Type> dp(n+1,INF); dp[0] = -INF;
    forn(i,n) {
        int l = int(upper_bound(all(dp),a[i])-begin(dp));
        if (dp[l-1] == a[i]) continue;
        prev[i] = idx[l-1], idx[l] = i, dp[l] = a[i];
    }
    dforn(i,n+1) {
        if (dp[i] < INF) {
            for (int k = idx[i]; k >= 0; k = prev[k]) seq.pb(k);
            reverse(all(seq));
            break;
        }
    }
    return seq;
}
