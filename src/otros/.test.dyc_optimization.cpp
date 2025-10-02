//https://codeforces.com/gym/103536/problem/A

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
#define dprint(v) cerr << #v " = " << v << endl
typedef long long ll;
typedef pair<int, int> pii;

int n, k; 
vector<ll> arr; 
vector<ll> pref;

ll C(int i, int j){
    return (pref[j] - pref[i]) * (j-i);
}

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    arr.resize(n); forn(i, n) cin >> arr[i];
    pref.pb(0);
    forn(i, n) pref.pb(pref.back() + arr[i]);
    dp_curr.resize(n, 0);
    dp_ant.resize(n, 1e17);
    forn(i, k){
        compute(0, n, 0, n);
        dp_ant = dp_curr;
    }
    cout << dp_curr[0] << endl;
}
