struct Edge {
   ll from;
   ll to;
   ll cost;
};

// ベルマンフォード法 (基本実装)
// 負閉路が存在する場合 true を返す
// distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
bool BellmanFord(vector<Edge>& edges, vector<ll>& dist, ll start) {
   fill(dist.begin(), dist.end(), INF);
   dist[start] = 0;
   // 負の閉路がなければ、(頂点数-1)回の更新で最短路が決まる
   rep(i, 0, (ll)dist.size()) {
      bool changed = false;
      // 各辺について
      for(const auto& edge : edges) {
         // to までの新しい距離
         const ll d = (dist[edge.from] + edge.cost);
         // d が現在の記録より小さければ更新
         if(d < dist[edge.to] && dist[edge.from] != INF) {
            dist[edge.to] = d;
            changed = true;
         }
      }
      if(!changed) { return false; }
   }
   // 負閉路が影響を与える範囲を計算
   // rep(i, 0, (ll)dist.size()){
   // 	// 各辺について
   // 	for (const auto& edge : edges){
   // 		// to までの新しい距離
   // 		const ll d = (dist[edge.from] + edge.cost);
   // 		// d が現在の記録より小さければ更新
   // 		if (d < dist[edge.to]&& dist[edge.from] != INF){
   // 			dist[edge.to] = -INF;
   // 		}
   // 	}
   // }
   // 頂点回数分だけループしても更新が続くのは, 負閉路が存在するから
   return true;
}