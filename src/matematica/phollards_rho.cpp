ll mulmod(ll a, ll b, ll m) { return ll(__int128(a) * b % m); }

ll expmod(ll b, ll e, ll m) { // O(log b)
	if (!e) return 1;
	ll q=expmod(b,e/2,m); q=mulmod(q,q,m);
	return e%2 ? mulmod(b,q,m) : q;
}

bool es_primo_prob(ll n, int a) {
	if (n == a) return true;
	ll s = 0, d = n-1;
	while (d%2 == 0) s++, d/=2;
	ll x = expmod(a,d,n);
	if ((x == 1) || (x+1 == n)) return true;
	forn(i,s-1){
		x = mulmod(x,x,n);
		if (x == 1) return false;
		if (x+1 == n) return true;
	}
	return false;
}
		
bool rabin(ll n) { // devuelve true sii n es primo
	if (n == 1)	return false;
	const int ar[] = {2,3,5,7,11,13,17,19,23};
	forn(j,9) if (!es_primo_prob(n,ar[j])) return false;
	return true;
}

ll rho(ll n) {
    if ((n & 1) == 0) return 2;
    ll x = 2, y = 2, d = 1;
    ll c = rand() % n + 1;
    while (d == 1) {
        x = (mulmod(x,x,n)+c)%n;
        y = (mulmod(y,y,n)+c)%n;
        y = (mulmod(y,y,n)+c)%n;
		d=gcd(x-y,n);
    }
    return d==n ? rho(n) : d;
}

void factRho(map<ll,ll>&prim, ll n){ //O (lg n)^3. un solo numero
	if (n == 1) return;
	if (rabin(n)) { prim[n]++; return; }
	ll factor = rho(n);
	factRho(factor, prim); factRho(n/factor, prim);
}
auto fact(ll n){
	map<ll,ll>prim;
	factRho(prim,n);
	return prim;
}