constexpr ll MOD = 1'000'000'007; // tmb es común 998'244'353
ll invmod[MAXN]; // inversos módulo MOD hasta MAXN
void invmods() { // todo entero en [2,MAXN] debe ser coprimo con MOD
    inv[1] = 1;
    forr(i, 2, MAXN) inv[i] = MOD - MOD/i*inv[MOD%i]%MOD;
}

// si MAXN es demasiado grande o MOD no es fijo:
// versión corta, m debe ser primo. O(log(m))
ll invmod(ll a, ll m) { return expmod(a,m-2,m); }
// versión larga, a y m deben ser coprimos. O(log(a)), en general más rápido
ll invmod(ll a, ll m) { return (extended_euclid(a,m).fst % m + m) % m; }
