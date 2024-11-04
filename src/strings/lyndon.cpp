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
