pair<ll,ll> extended_euclid(ll a, ll b) {
    if (b == 0) return {1, 0};
    auto [y, x] = extended_euclid(b, a%b);
    y -= (a/b)*x;
    if (a*x + b*y < 0) x = -x, y = -y;
    return {x, y}; // a*x + b*y = gcd(a,b)
}
