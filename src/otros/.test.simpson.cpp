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

double simpson(auto f, double a, double b, int n=1e4) {
    double h = (b-a)/2/n, s = f(a);
    forr(i,1,2*n) s += f(a+i*h) * ((i%2)?4:2);
    return (s+f(b))*h/3;
}

constexpr double pi = acos(-1);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(DECIMAL_DIG);

    double a, b;
    int n;
    cin >> a >> b >> n;

    auto f = [&](double x) {
      static double ha = a/2, hb = b/2;
      return pi*ha*ha*(1-(x*x)/(hb*hb));
    };
    int blocks = 1e6, range = blocks/n;
    double start = -b/2, step = b/n;
    forn(i,n) {
        double l = start+i*step, r=l+step;
        cout << simpson(f,l,r,range) << endl;
    }
}
