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

struct Manacher {
	vector<int> p;
	Manacher(string const& s) {
		int n = sz(s), m = 2*n+1, l = -1, r = 1;
		vector<char> t(m); forn(i, n) t[2*i+1] = s[i];
		p.resize(m); forr(i, 1, m) {
			if (i < r) p[i] = min(r-i, p[l+r-i]);
			while (p[i] <= i && i < m-p[i] && t[i-p[i]] == t[i+p[i]]) ++p[i];
			if (i+p[i] > r) l = i-p[i], r = i+p[i];
		}
	}
	pii at(int i) const {int k = p[i]-1; return pair{i/2-k/2, k};}
	pii odd(int i) const {return at(2*i+1);}
	pii even(int i) const {return at(2*i);}
};


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

	string s;
	cin >> s;

	int n = sz(s);
	Manacher m(s);
	int largo = 0, c = 0;
	forn(i, n) {
			auto [a,b] = m.odd(i);
			if (b>largo) largo=b, c=a;
			auto [a2,b2] = m.even(i);
			if (b2>largo) largo=b2, c=a2;
	}

	forr(i, c, c+largo) cout << s[i];
	cout << endl;
}
