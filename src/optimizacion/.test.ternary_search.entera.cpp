// https://codeforces.com/contest/439/problem/D

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

ll ternary(auto f, ll l, ll r) {
    for (ll d = r-l; d > 2; d = r-l) {
        ll a = l+d/3, b = r-d/3;
        if (f(a) > f(b)) l = a; else r = b;
    }
    return l+1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    forn(i, n) cin >> a[i];
    forn(j, m) cin >> b[j];

    constexpr ll l = -1, r = 1'000'000'001;
    const auto f = [&](const ll k) {
        ll ans = 0;
        forn(i, n) ans += max(0LL, k-a[i]);
        forn(j, m) ans += max(0LL, b[j]-k);
        return ans;
    };
    const ll k = ternary(f,l,r);
    cout << f(k) << endl;
}
