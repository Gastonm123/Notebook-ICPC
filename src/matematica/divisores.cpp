// Usar asi: divisores(fac, divs, fac.begin()); NO ESTA ORDENADO
void divisores(const map<ll,ll> &f, vector<ll> &divs, auto it, ll n=1){
    if (it==f.begin()) divs.clear();
    if (it==f.end()) { divs.pb(n); return; }
    ll p=it->fst, k=it->snd; ++it;
    forn(_, k+1) divisores(f,divs,it,n), n*=p;
}