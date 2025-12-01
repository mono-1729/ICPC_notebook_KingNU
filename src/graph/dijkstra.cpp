vector<ll> dijkstra(int s, vector<vector<pair<int, ll>>> &g){
    int n = (int)g.size();
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    vector<ll> dist(n, INF);
    que.push(make_pair(0, s));
    dist[s] = 0;
    while(!que.empty()){
        auto [d, u] = que.top(); que.pop();
        if(dist[u] < d) continue;
        for(auto [v, c]: g[u]){
            if(dist[v] > d+c){
                dist[v] = d+c;
                que.push({dist[v], v});
            }
        }
    }
    return dist;
}
