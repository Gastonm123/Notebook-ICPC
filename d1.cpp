#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cout << #v "=" << v << endl //;)
#define forr(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) forr(i, 0, n)
#define dforn(i, n) for (int i = n - 1; i >= 0; i--)
#define forall(it, v) for (auto it = v.begin(); it != v.end(); ++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> ii;

// https://codeforces.com/contest/1995/problem/D

int n;

const int MAXN = 1<<18;
int A[MAXN];   // A[MASK] son las ventanas con todos menos los elementos de la mascara
int ACC[MAXN];  // ACC[MASK] es verdadero si hay ventanas que no funcionarian con la mascara: pueden
                // no funcionar para un superconjunto de la mascara, o la misma.
int MAXMASK;

int calc_ans() {
    forn (bit, 18) {
        for (int i = MAXMASK-1; i>=0; i--) {
            if (!((i>>bit) & 1)) {
                A[i] |= A[i|(1<<bit)];
            }
        }
    }
    /*
    for (int i = MAXMASK-1; i>=0; i--) {
        ACC[i] = (A[i] > 0);
        forn (bit, 18) { // itera por las mascaras que tienen un bit mas encendido
            if (i & (1<<bit))
                continue;

            ACC[i] |= ACC[i|(1<<bit)];
        }
    }
    */
    int minimo = 19;
    forr (i, 1, MAXMASK) {
        if (A[i] == 0) {
            minimo = min(minimo, __builtin_popcount(i));
        }
    }
    return minimo;
}

#define ch(idx) (text[idx]-'A')

int main()
{
    ios::sync_with_stdio(0);
    
    int t; cin >> t; forn(tc, t) {
        int n, c, k; cin >> n >> c >> k;

        string _text;
        cin >> _text;
        vector<char> text(n+k);
        forn (i, n) text[i] = _text[i];
        forn (i, k) text[n+i] = _text[n-1];

        vector<int> ventana(18, 0);
        forn (i, k) {
            ventana[ch(i)]++;
        }

        MAXMASK = 1<<c;

        forr (i, k, n+k) {
            int mask = 0;
            forn (j, 18) {
                if (ventana[j] > 0)
                    mask += 1<<j;
            }

            // forn (j, 18) cout << ventana[j] << " "; cout << endl;
            // cout << ((~mask) & (MAXN-1)) << endl;
            A[(~mask) & (MAXMASK-1)]++;
            ventana[ch(i-k)]--;
            ventana[ch(i)]++;
        }

        cout << calc_ans() << endl;
        fill(A, A+MAXMASK, 0);
        fill(ACC, ACC+MAXMASK, 0);
    }


    return 0;
}