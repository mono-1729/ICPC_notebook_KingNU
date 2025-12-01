template<class T>
struct SegmentTree {
    static constexpr T unit = INT_MAX;
    T op(T a, T b){ return min(a, b); } 
    vector<T> s;
    int _n, n;
    SegmentTree(int n_ = 0, T def = unit): _n(n_) {
        int log = 1; 
        while((1 << log) < n_) log++;
        n = 1<<log;
        s = vector<T>(n*2, def);
    }
    // s[i] = x; 
    void update(int i, T x) {
        i += n;
        s[i] = x;
        while(i >>= 1){
            s[i] = op(s[2 * i], s[2 * i + 1]);
        }
    }
    // s[i] = f(s[i], x);
    void apply(int i, T x){
        i += n;
        s[i] = op(s[i], x);
        while(i >>= 1){
            s[i] = op(s[2 * i], s[2 * i + 1]);
        }
    }
    // 区間取得: [b, e)
    T query(int b, int e){
        T ra = unit, rb = unit;
        for(b += n, e += n; b < e; b /= 2, e /= 2){
            if (b % 2) ra = op(ra, s[b++]);
            if (e % 2) rb = op(s[--e], rb);
        }
        return op(ra, rb);
    }
    // セグ木上の二分探索 O(log{n}) (optional)
    // ex int L = lst.max_right(0, [&](int tmp){return tmp < l[i];});
    template<class F> int max_right(int l, F f){
        if(l == _n) return _n;
        l += n;
        T sm = unit;
        do{
            while(l % 2 == 0) l >>= 1;
            if(!f(op(sm, s[l]))){
                while(l < n){
                    l = (2 * l);
                    if(f(op(sm, s[l]))){
                        sm = op(sm, s[l]);
                        l++;
                    }
                }
                return l - n;
            }
            sm = op(sm, s[l]);
            l++;
        }while((l & -l) != l);
        return _n;
    }
    template<class F> int min_left(int r, F f){
        if(r == 0) return 0;
        r += n;
        T sm = unit;
        do {
            r--;
            while(r > 1 && (r % 2)) r >>= 1;
            if(!f(op(s[r], sm))){
                while(r < n){
                    r = (2 * r + 1);
                    if(f(op(s[r], sm))){
                        sm = op(s[r], sm);
                        r--;
                    }
                }
                return r + 1 - n;
            }
            sm = op(s[r], sm);
        }while((r & -r) != r);
        return 0;
    }
};
