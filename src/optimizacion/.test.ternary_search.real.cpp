// https://codeforces.com/contest/578/problem/C

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

double golden(auto f, double l, double r, int iters) {
    constexpr double ratio = (3-sqrt(5))/2;
    double x1 = l+(r-l)*ratio, f1 = f(x1);
    double x2 = r-(r-l)*ratio, f2 = f(x2);
    while (iters--) {
        if (f1 > f2) l=x1, x1=x2, f1=f2, x2=r-(r-l)*ratio, f2=f(x2);
        else         r=x2, x2=x1, f2=f1, x1=l+(r-l)*ratio, f1=f(x1);
    }
    return (l+r)/2;
}

int n;
vector<int> a;

double sum(double m, double sign) {
    vector<double> b(n,sign);
    forn(i, n) b[i] *= double(a[i]) + m;
    double curr = 0, best = 0;
    forn(i, n) {
        curr = max(0.0,curr+b[i]);
        best = max(best,curr);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(DECIMAL_DIG);

    cin >> n;
    a.resize(n);
    forn(i, n) cin>>a[i];

    constexpr double l = -2e9, r = 2e9;
    auto f = [&](double m) { return max(sum(m,1),sum(m,-1)); };
    const double x = golden(f,l,r,100);
    cout << f(x) << '\n';

}
