// need SCC
struct TWO_SAT {
    int _n;
    vector<bool> answer;
    SCC scc;
    TWO_SAT(int n=0) : _n(n), answer(n), scc(2 * n) {}
    // if(f is true) x_i; else \bar{x_i}
    // if(g is true) x_j; else \bar{x_j}
    void add_clause(int i, bool f, int j, bool g) {
        scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
    }
    bool satisfiable() {
        auto id = scc.scc_ids().second;
        for (int i = 0; i < _n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            answer[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
};