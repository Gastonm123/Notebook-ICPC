struct TreeCanonizer { // hashing de arboles enraizados
    map<vector<int>, int> idOf; // hijos ordenados -> id
    int canonicalId(int u, int p, const vector<vector<int>>& adj) {
        vector<int> childIds;
        for (int v : adj[u]) if (v != p)
            childIds.push_back(canonicalId(v, u, adj));
        sort(childIds.begin(), childIds.end());// normalizar
        return idOf.try_emplace(childIds, (int)idOf.size()).first->second;
    }
};
// isomorfos sii, con UNA instancia compartida:
// c.canonicalId(r1,-1,adj1) == c.canonicalId(r2,-1,adj2)
// Sin raiz: enraizar en el/los centroidos y comparar {id(c1),id(c2)}