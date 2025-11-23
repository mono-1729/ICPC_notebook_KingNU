class xor_set {
   private:
   vector<ll> w;

   public:
   xor_set() {}
   void insert(ll x) {
      for(ll v : w)
         if(v & -v & x) x ^= v;
      if(x == 0) return;
      for(ll& v : w)
         if(x & -x & v) v ^= x;
      w.push_back(x);
   }
   // 独立か判定
   ll count(ll x) {
      for(ll v : w)
         if(v & -v & x) x ^= v;
      if(x == 0) return 1;
      else return 0;
   }
   vector<ll> get() { return w; }
};