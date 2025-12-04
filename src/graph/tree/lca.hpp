struct LCA {
    int LOG;
    vector<int> dep;
    vector<vector<int>> par;

    LCA(int n) : LOG(0), dep(n) {
        while ((1 << LOG) <= n) LOG++;
        par.assign(LOG, vector<int>(n, -1));
    }

    void build(const vector<vector<int>>& g, int root = 0) {
        queue<int> q;
        q.push(root);
        dep[root] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : g[v]) {
                if (u == par[0][v]) continue;
                par[0][u] = v;
                dep[u] = dep[v] + 1;
                q.push(u);
            }
        }

        for (int k = 1; k < LOG; k++) {
            for (int v = 0; v < (int)g.size(); v++) {
                int p = par[k - 1][v];
                par[k][v] = (p < 0 ? -1 : par[k - 1][p]);
            }
        }
    }

    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        int d = dep[a] - dep[b];

        for (int k = 0; k < LOG; k++) {
            if (d >> k & 1) a = par[k][a];
        }
        if (a == b) return a;

        for (int k = LOG - 1; k >= 0; k--) {
            if (par[k][a] != par[k][b]) {
                a = par[k][a];
                b = par[k][b];
            }
        }
        return par[0][a];
    }
};