// https://cses.fi/problemset/task/1110

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

// única secuencia no-creciente de strings menores a sus rotaciones
vector<pii> lyndon(string const& s) {
    vector<pii> fs;
    int n = sz(s);
    for (int i = 0, j, k; i < n;) {
        for (k = i, j = i+1; j < n && s[k] <= s[j]; ++j)
            if (s[k] < s[j]) k = i; else ++k;
        for (int m = j-k; i <= k; i += m) fs.emplace_back(i, m);
    }
    return fs; // retorna substrings de la forma {comienzo, largo}
}

// último comienzo de la mínima rotación
int minrot(string const& s) {
    auto fs = lyndon(s+s);
    int n = sz(s), start = 0;
    for (auto f : fs) if (f.fst < n) start = f.fst; else break;
    return start;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    string s;
	cin >> s;
	int start = minrot(s);
	auto rot = s.substr(start) + s.substr(0, start);
	cout << rot << endl;
}
