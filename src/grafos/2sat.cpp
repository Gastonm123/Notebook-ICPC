struct TwoSatSolver{
    int n_vars; 
    int n_vertices;
    vector<vector<int>> adj, adj_t;
    vector<bool> used;
    vector<int> order,comp;
    vector<bool> assignment;
    TwoSatSolver(int _n_vars) : n_vars(_n_vars),
        n_vertices(2*n_vars), adj(n_vertices),
        adj_t(n_vertices), used(n_vertices),
        order(), comp(n_vertices, -1), assignment(n_vars){
        order.reserve(n_vertices);
    } 
    void dfs1(int v){
        used[v] = true;
        for(int u : adj[v]){
            if(!used[u]) dfs1(u);
        }
        order.pb(v);
    }
    void dfs2(int v, int c1){
        comp[v] = c1;
        for(int u : adj_t[v]){
            if(comp[u] == -1) dfs2(u, c1);
        }
    }
    bool solve_2SAT(){
        order.clear();
        used.assign(n_vertices, false);
        forn(i, n_vertices){
            if(!used[i]) dfs1(i);
        }
        comp.assign(n_vertices, -1);
        for(int i = 0, j = 0; i < n_vertices; ++i){
            int v = order[n_vertices - i - 1];
            if(comp[v] == -1) dfs2(v, j++);
        }
        assignment.assign(n_vars, false);
        for(int i = 0; i < n_vertices; i+=2){
            if(comp[i] == comp[i+1]) return false;
            assignment[i/2] = comp[i] > comp[i+1];
        }
        return true;
    }
    void add_disjunction(int a, bool na, int b, bool nb){
        a = 2 * a ^ na;
        b = 2 * b ^ nb;
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        adj[neg_a].pb(b);
        adj[neg_b].pb(a);
        adj_t[b].pb(neg_a);
        adj_t[a].pb(neg_b);
    }
};