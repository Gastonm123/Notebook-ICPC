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
