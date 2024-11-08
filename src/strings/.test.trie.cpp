// https://www.spoj.com/problems/PHONELST/

#include <bits/stdc++.h>
using namespace std;

#define forr(i, a, b) for (int i = int(a); i < int(b); i++)
#define forn(i, n) forr(i,0,n)
#define dforr(i, a, b) for (int i = int(b)-1; i >= int(a); i--)
#define dforn(i, n) dforr(i,0,n)
#define all(v) begin(v),end(v)
#define sz(v) (int((v).size()))
#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define endl '\n'
#define dprint(v) cerr << #v " = " << v << endl

typedef long long ll;
typedef pair<int, int> pii;

// trie genérico. si es muy lento, se puede modificar para que los hijos sean
// representados con un array del tamaño del alfabeto
template<class Char> struct Trie {
    struct Node {
        map<Char, Node*> child;
        bool term;
    };
    Node* root;
    static inline deque<Node> nodes;
    static Node* make() {
        nodes.emplace_back();
        return &nodes.back();
    }
    Trie() : root{make()} {}
    // retorna el largo del mayor prefijo de s que es prefijo de algún string
    // insertado en el trie
    int find(basic_string<Char> const& s) const {
        Node* curr = root;
        forn(i,sz(s)) {
            auto it = curr->child.find(s[i]);
            if (it == end(curr->child)) return i;
            curr = it->snd;
        }
        return sz(s);
    }
    // inserta s en el trie
    void insert(basic_string<Char> const& s) {
        Node* curr = root;
        forn(i,sz(s)) {
            auto it = curr->child.find(s[i]);
            if (it == end(curr->child)) curr = curr->child[s[i]] = make();
            else curr = it->snd;
        }
        curr->term = true;
    }
    // elimina s del trie
    void erase(basic_string<Char> const& s) {
        auto erase = [&](auto&& me, Node* curr, int i) -> bool {
            if (i == sz(s)) {
                curr->term = false;
                return sz(curr->child) == 0;
            }
            auto it = curr->child.find(s[i]);
            if (it == end(curr->child)) return false;
            if (!me(me,it->snd,i+1)) return false;
            curr->child.erase(it);
            return sz(curr->child) == 0;
        };
        erase(erase,root,0);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> nums(n);
    Trie<char> trie;
    forn(i,n) {
        cin >> nums[i];
        trie.insert(nums[i]);
    }

    forn(i,n) {
        auto curr = trie.root;
        for (char dig : nums[i]) {
            if (curr->term) {
                cout << "NO" << endl;
                return;
            }
            curr = curr->child[dig];
        }
        if (sz(curr->child) != 0) {
            cout << "NO" << endl;
            return;
        }
        trie.erase(nums[i]);
    }
    cout << "YES" << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
}
