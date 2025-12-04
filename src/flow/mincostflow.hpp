struct mcf_graph {
    struct edge {
        int to, rev;
        ll cap, cost;
    };
    int N;
    vector<vector<edge>> G;
    vector<pair<int, int>> pos;
    vector<int> pu, pe;
    vector<ll> H, D; // ポテンシャル H はここに保存される
    mcf_graph(int n = 0) : N(n), G(n), pu(n), pe(n) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        int ui = (int)G[u].size(), vi = (int)G[v].size();
        pos.emplace_back(u, ui);
        G[u].emplace_back(v, vi, cap, cost);
        G[v].emplace_back(u, ui, 0, -cost);
    }
    pair<ll, ll> flow(int s, int t, ll lim = INF) { return slope(s, t, lim).back(); }
    vector<pair<ll, ll>> slope(int s, int t, ll lim = INF) {
        vector<pair<ll, ll>> res = {{0, 0}};
        ll flow = 0, cost = 0;        
        H.assign(N, 0); 
        while (flow < lim) {
            D.assign(N, INF);
            /* ここから O(N^2) ダイクストラ */
            vector<bool> vis(N);
            D[s] = 0;
            ll d = INF;
            while (true) {
                int u = -1;
                d = INF;
                for (int i = 0; i < N; i++) {
                    if (!vis[i] && chmin(d, D[i])) u = i;
                }
                if (u == -1) break;
                vis[u] = true;
                for (int i = 0; i < ssize(G[u]); i++) {
                    auto e = G[u][i];
                    int v = e.to;
                    if (e.cap > 0) {
                        d = D[u] + e.cost + H[u] - H[v];
                        if (chmin(D[v], d)) { pu[v] = u, pe[v] = i; }
                    }
                }
            }
            /* ここまで */
            /* ここから O(MlogN) ダイクストラ
            using P = pair<ll, int>;
            priority_queue<P, vector<P>, greater<P>> q;
            D[s] = 0;
            q.emplace(0, s);
            while (q.size()) {
                auto [d, u] = q.top();
                q.pop();
                if (d > D[u]) continue;
                for (int i = 0; i < ssize(G[u]); i++) {
                    auto &e = G[u][i];
                    int v = e.to;
                    if (e.cap > 0) {
                        if (chmin(D[v], d + e.cost + H[u] - H[v])) {
                            q.emplace(D[v], v);
                            pu[v] = u, pe[v] = i;
                        }
                    }
                }
            }
            ll d;
            ここまで */
            if (D[t] == INF) break;
            for (int i = 0; i < N; i++) {
                if (D[i] < INF) H[i] += D[i];
            }
            d = lim - flow;
            for (int i = t; i != s; i = pu[i]) chmin(d, G[pu[i]][pe[i]].cap);
            flow += d;
            cost += d * H[t];
            res.emplace_back(flow, cost);
            for (int i = t; i != s; i = pu[i]) {
                auto& e = G[pu[i]][pe[i]];
                e.cap -= d;
                G[i][e.rev].cap += d;
            }
        }
        return res;
    }
    vector<tuple<int, int, ll, ll, ll>> edges() {
        vector<tuple<int, int, ll, ll, ll>> res;
        for (auto [u, i] : pos) {
            auto e = G[u][i];
            auto re = G[e.to][e.rev];
            res.emplace_back(u, e.to, e.cap + re.cap, re.cap, e.cost);
        }
        return res;
    }
};