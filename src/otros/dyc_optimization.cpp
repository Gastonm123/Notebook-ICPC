vector<ll> dp_ant, dp_curr;

void compute(int l, int r, int optl, int optr){
    if(l == r) return;
    int m = (l+r)/2;
    ll dpm = 1e17;
    int optm = -1;   
    forr(i, max(m+1, optl), optr+1){
        ll cost = C(m, i) + (i == n ? 0 : dp_ant[i]);
        if(cost < dpm) dpm = cost, optm = i;
    }
    dp_curr[m] = dpm;
    compute(l, m, optl, optm);
    compute(m+1, r, optm, optr);
}


forn(i, k){
    compute(0, n, 0, n);
    dp_ant = dp_curr;
}
cout << dp_curr[0] << endl;

