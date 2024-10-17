#include <bits/stdc++.h>
using namespace std;

#define forr(i, a, b) for (int i = int(a); i < int(b); i++)
#define forn(i, n) forr(i,0,n)
#define dforr(i, a, b) for (int i = int(b)-1; i >= int(a); i--)
#define dforn(i, n) dforr(i,0,n)
#define all(v) begin(v),end(v)
#define sz(v) (int(size(v)))
#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define endl '\n'
#define dprint(v) cout << #v " = " << v << endl

typedef long long ll;
typedef pair<int, int> pii;

constexpr ll MOD = 1'000'000'007;

pair<ll,ll> extended_euclid(ll a, ll b) {
    if (b == 0) return {1, 0};
    auto [y, x] = extended_euclid(b, a%b);
    y -= (a/b)*x;
    if (a*x + b*y < 0) x = -x, y = -y;
    return {x, y};
}

ll invmod(ll a, ll m) { return (extended_euclid(a,m).fst % m + m) % m; }

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int _t_;
    cin >> _t_;
    while(_t_--){

        int n;
        cin >> n;
        vector<ll> a(n);
        forn(i,n) cin >> a[i];

        vector<ll> psum(n+1);
        forn(i,n) psum[i+1] = (psum[i] + a[i]) % MOD;
        ll num = 0;
        forn(i,n) {
            ll sum = (MOD + psum[n] - psum[i+1]) % MOD;
            num = (num + a[i] * sum) % MOD;
        }
        ll denom = n * ll(n-1) % MOD * invmod(2, MOD) % MOD;
        cout << num * invmod(denom, MOD) % MOD << endl;

    }
}
