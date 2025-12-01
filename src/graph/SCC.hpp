struct SCC{
    int _n;
    vector<vector<int>> g;
    SCC(int n) : _n(n), g(n) {}
    // add edge
    void add_edge(int from, int to){ g[from].push_back(to); }
    // @return pair of (number of scc components, scc id)
    pair<int, vector<int>> scc_ids() {
        int now_ord = 0, group_num = 0;
        vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for(auto to: g[v]){
                if(ord[to] == -1){
                    self(self, to);
                    low[v] = min(low[v], low[to]);
                }else{
                    low[v] = min(low[v], ord[to]);
                }
            }
            if(low[v] == ord[v]){
                while(true){
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if(u == v) break;
                }
                group_num++;
            }
        };
        rep(i, 0, _n) if(ord[i] == -1) dfs(dfs, i);
        for(auto& x: ids) x = group_num-1-x;
        return {group_num, ids};
    }
    // get scc (topological sorted)
    vector<vector<int>> scc(){
        auto ids = scc_ids();
        int group_num = ids.first;
        vector<int> counts(group_num);
        for(auto x : ids.second) counts[x]++;
        vector<vector<int>> groups(ids.first);
        rep(i, 0, group_num) groups[i].reserve(counts[i]);
        rep(i, 0, _n) groups[ids.second[i]].push_back(i);
        return groups;
    }
};