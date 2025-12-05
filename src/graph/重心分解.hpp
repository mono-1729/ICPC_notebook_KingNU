{
    vector<bool> used(n); // 重心として除いているかどうか
    vector<int> sz(n);    // 部分木のサイズ

    auto get_centroid = [&](int v) {
        // DFS1：部分木のサイズを求める O(n)
        auto dfs = [&](auto f, int pos, int pre=-1) -> int {
            sz[pos] = 1;
            for(auto nxt: g[pos]){
                if(nxt == pre || used[nxt]) continue;
                sz[pos] += f(f, nxt, pos);
            }
            return sz[pos];
        };
        int total = dfs(dfs, v), c = -1;
        // DFS2：重心を求める O(n)
        auto dfs2 = [&](auto f, int pos, int pre=-1) -> void {
            bool ok = (total-sz[pos])*2 <= total;
            for(auto nxt: g[pos]){
                if(nxt == pre || used[nxt]) continue;
                f(f, nxt, pos);
                if(sz[nxt]*2 > total) ok = false;
            }
            if(ok) c = pos;
        };
        dfs2(dfs2, v);
        return c;
    };
}