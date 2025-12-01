struct Edge{ 
   int from, to;
   ll cost; 
};
vector<ll> bellman_ford(vector<Edge> &edges, int n, int start){
   vector<ll> dist(n, INF);
	dist[start] = 0;
	rep(i, 0, n-1){
		for (auto edge : edges){
			ll d = (dist[edge.from] + edge.cost);
			if (dist[edge.from] != INF && d < dist[edge.to]){
				dist[edge.to] = d;
			}
		}
	}

	rep(i, 0, n){
		for (auto edge : edges){
		   ll d = (dist[edge.from] + edge.cost);
			if(d < dist[edge.to] && dist[edge.from] != INF){
				dist[edge.to] = -INF; // 更新されたら無限に小さくなる
			}
		}
	}
    return dist;
}
