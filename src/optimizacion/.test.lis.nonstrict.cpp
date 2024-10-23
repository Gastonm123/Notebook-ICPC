// https://codeforces.com/problemset/problem/582/B

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

constexpr int INF = 1e9+7;

template<class Type> vector<int> lis(vector<Type>& a) {
    int n = sz(a);
    vector<int> seq, prev(n,-1), idx(n+1,-1);
    vector<Type> dp(n+1,INF); dp[0] = -INF;
    forn(i,n) {
        int l = int(upper_bound(all(dp),a[i])-begin(dp));
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, t;
    cin >> n >> t;
    vector<int> arr(n);
    forn(i, n) cin >> arr[i];

    int b = min(n, t);
    forn(_, b-1) forn(i, n) arr.push_back(arr[i]);
    int s1 = sz(lis(arr)), s2 = s1;
    if (b < t) {
        forn(i, n) arr.push_back(arr[i]);
        s2 = sz(lis(arr));
    }

    cout << s1+(s2-s1)*(t-b) << endl;
}
