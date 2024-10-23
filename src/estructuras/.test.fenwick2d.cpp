//https://cses.fi/problemset/result/10807168/
#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cerr << #v "=" << v << endl
#define forr(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) forr(i, 0, n)
#define dforn(i, n) for (int i = n - 1; i >= 0; i--)
#define forall(it, v) for (auto it = v.begin(); it != v.end(); ++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define all(v) begin(v),end(v)
#define endl '\n'
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
const int N = 1001, M =1001;

struct Fenwick2D{
    ll t[N][M]={};
    void adjust(int p, int q, ll v){
        for(int i=p+1;i<N;i+=(i&-i))
            for(int j= q+1; j<M; j+=(j&-j))
                t[i][j]+=v;
    }
    ll sum(int p,int q){ // suma [0,p)
        ll s = 0;
        for(int i=p;i;i-=(i&-i))
            for(int j=q; j; j-=(j&-j))
                s+=t[i][j];
        return s;
    }
    ll sum(int x1, int y1, int x2, int y2){return sum(x2,y2)-sum(x1,y2)-sum(x2,y1)+sum(x1,y1);} // suma [a,b)
};

int main(int argc, char **argv){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if(argc == 2) freopen(argv[1], "r", stdin);
    int n, q; cin >> n >> q;
    Fenwick2D f;
    forn(i, n)forn(j, n){
        char c; cin >> c;
        if(c=='*') f.adjust(i,j,1);
    }
    forn(i, q){
        int t; cin >> t;
        if(t == 1){
            int i, j; cin >> i >> j; i--; j--;
            if(f.sum(i,j,i+1,j+1)) f.adjust(i,j,-1);
            else f.adjust(i,j,1);
        }
        else{
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; x1--; y1--;
            cout << f.sum(x1,y1,x2,y2) << endl;
        }
    }
}
