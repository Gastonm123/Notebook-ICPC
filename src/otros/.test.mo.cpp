//https://codeforces.com/contest/220/problem/B
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b)  for(int i = int(a); i < int(b); i++)
#define forn(i,n)    forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define all(v)       begin(v), end(v)
#define mp           make_pair
#define sz(v)        int(v.size())
#define pb           push_back
#define fst          first
#define snd          second
#define endl         '\n'
#define dprint(x)    cerr << #x << " = " << (x) << endl
    
using ll = long long;
vector<int> cant;
vector<int> arr;
const int MAXN = 1e5+100;
int n,sq,nq; // array size, sqrt(array size), #queries
struct qu{int l,r,id;};
qu qs[MAXN];
ll ans[MAXN]; // ans[i] = answer to ith query
bool qcomp(const qu &a, const qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}

int res;
void add(int j){
    int i = arr[j];
    if(i > n) return;
    cant[i]++;
    if(cant[i] == i) res++;
    if(cant[i] == i+1) res--;
}
    
void remove(int j){
    int i = arr[j];
    if(i > n) return;
    cant[i]--;
    if(cant[i] == i) res++;
    if(cant[i] == i-1) res--;
}
void mos(){
    forn(i,nq)qs[i].id=i;
    sq=sqrt(n)+.5;
    sort(qs,qs+nq,qcomp);
    int l=0,r=0;
    cant.resize(n+2,0);
    res = 0;
    forn(i,nq){
        qu q=qs[i];
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        ans[q.id]=res;
    }
}


    
int main (int argc, char** argv) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (argc == 2) freopen(argv[1], "r", stdin);
    cin >> n >> nq;
    forn(i, n){
        int ai; cin >> ai;
        arr.pb(ai);
    }
    forn(i, nq){
        int l, r; cin >> l >> r;
        l--;
        qs[i]={l,r,i};
    }
    mos();
    forn(i, nq) cout << ans[i] << endl;
    return 0;
}