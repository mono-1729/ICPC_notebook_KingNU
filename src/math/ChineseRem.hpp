inline ll mod(ll a, ll m) { return (a % m + m) % m; }

inline ll mul(ll a, ll b, ll m) {
   a = mod(a, m);
   b = mod(b, m);
   if(b == 0) return 0;
   ll res = mul(mod(a + a, m), b >> 1, m);
   if(b & 1) res = mod(res + a, m);
   return res;
}

// returns gcd(a, b) and assign x, y to integers
// s.t. ax + by = gcd(a, b) and |x| + |y| is minimized
ll extgcd(ll a, ll b, ll& x, ll& y) {
   // assert(a >= 0 && b >= 0);
   if(!b) return x = 1, y = 0, a;
   ll d = extgcd(b, a % b, y, x);
   y -= a / b * x;
   return d;
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x = r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<ll, ll> chineseRem(const vector<ll>& b, const vector<ll>& m) {
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