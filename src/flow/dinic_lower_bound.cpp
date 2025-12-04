// need: Dinic
template <class F>
struct maximum_flow_lr {
    F flow;
    int S, T;
    ll sum_lb;

    maximum_flow_lr() {}

    maximum_flow_lr(int n) : flow(n + 2), S(n), T(n + 1), sum_lb(0) {}

    void add_edge(int u, int v, ll lb, ll ub) {
        assert(0 <= lb);
        assert(lb <= ub);
        if (u == v || ub == 0) return;
        flow.add_edge(u, v, ub - lb);
        // Three lines below should have no effect if lb == 0.
        flow.add_edge(S, v, lb);
        flow.add_edge(u, T, lb);
        sum_lb += lb;
    }

    ll max_flow(int s, int t) {
        ll a = flow.flow(S, T);
        ll b = flow.flow(s, T);
        ll c = flow.flow(S, t);
        ll d = flow.flow(s, t);
        return (a + c == sum_lb && a + b == sum_lb) ? b + d : -1;
    }
};
