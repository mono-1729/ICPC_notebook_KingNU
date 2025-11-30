struct Tree {
   typedef int T;
   static constexpr T unit = INT_MIN;
   T f(T a, T b) { return max(a, b); }  // (any associative fn)
   vector<T> s;
   int n;
   Tree(int n_ = 0, T def = unit){
    ll log = 1;
    while((1<<log) < n_) log++;
    n = 1<<log;
    s = vector<T>(n*2,def);
   }
   T query(int b, int e) {  // query [b, e)
      T ra = unit, rb = unit;
      for(b += n, e += n; b < e; b /= 2, e /= 2) {
         if(b % 2) ra = f(ra, s[b++]);
         if(e % 2) rb = f(s[--e], rb);
      }
      return f(ra, rb);
   }
};