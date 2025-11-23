inline ll mod(ll a, ll m) { return (a % m + m) % m; }

inline long long mul(long long a, long long b, long long m) {
   a = mod(a, m);
   b = mod(b, m);
   if(b == 0) return 0;
   long long res = mul(mod(a + a, m), b >> 1, m);
   if(b & 1) res = mod(res + a, m);
   return res;
}

// 拡張ユークリッドの互除法
// ap+bq=gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします。
ll extGCD(ll a, ll b, ll& p, ll& q) {
   if(b == 0) {
      p = 1;
      q = 0;
      return a;
   }
   ll d = extGCD(b, a % b, q, p);
   q -= a / b * p;
   return d;
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x = r (mod. m)
// 解なしの場合は (0, -1) をリターン
pll chineseRem(const vector<ll>& b, const vector<ll>& m) {
   ll r = 0, M = 1;
   rep(i, 0, (int)b.size()) {
      ll p, q;
      ll d = extGCD(M, m[i], p, q);  // p is inv of m1/d (mod. m[i]/d)
      if((b[i] - r) % d != 0) return {0, -1};
      ll tmp = mul(((b[i] - r) / d), p, (m[i] / d));
      r += M * tmp;
      M *= m[i] / d;
   }
   return {mod(r, M), M};
}