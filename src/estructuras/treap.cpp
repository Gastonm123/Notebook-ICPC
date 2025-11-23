// representa una lista como arbol con el orden implicito
struct node {
	int val, prio, tam;
	node *l, *r;
};
node *make(int val) {
    return new node { val, rand(), 1, nullptr, nullptr };
}
int tam(node *n) { return n ? n->tam : 0; }
void recalc(node *n) { n->tam = tam(n->l) + 1 + tam(n->r); }
node* merge(node* s, node* t) {
    if (s == nullptr) return t;
    if (t == nullptr) return s;
    if (s->prio > t->prio) {
        s->r = merge(s->r, t);
        recalc(s);
        return s;
    } else {
        t->l = merge(s, t->l);
        recalc(t);
        return t;
    }
}
pair<node*, node*> split(node *s, int k) {
    if (s == nullptr) return {nullptr, nullptr};
    if (tam(s->l) < k) {
        if (s->l == nullptr) return {nullptr, nullptr};
        auto [l, r] = split(s->r, k-tam(s->l)-1);
        s->r = l;
        recalc(s);
        return {s, r};
    } else {
        auto [l, r] = split(s->l, k);
        s->l = r;
        recalc(s);
        return {l, s};
    }
} // usage: node *list = nullptr; list = merge(list, make(5))