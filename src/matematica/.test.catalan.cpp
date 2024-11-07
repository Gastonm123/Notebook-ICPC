https://cses.fi/problemset/task/2064/
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
const int MAXN = 1e6+100;
const int M = 1e9+7;
ll F[MAXN], INV[MAXN], FI[MAXN];

ll Cat(int n){
    return ((F[2*n] *FI[n+1])%M *FI[n])%M;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    F[0] = 1; forr(i, 1, MAXN) F[i] = F[i-1]*i %M;
    INV[1] = 1; forr(i, 2, MAXN) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
    FI[0] = 1; forr(i, 1, MAXN) FI[i] = FI[i-1]*INV[i] %M;
    int n; cin >> n;
    if(n%2) cout << 0 << endl;
    else cout << Cat(n/2) << endl;
}