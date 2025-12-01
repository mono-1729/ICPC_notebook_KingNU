template<class T>
struct SegmentTree {
    static constexpr T unit = INT_MAX;
    T f(T a, T b) { return min(a, b); } 
    vector<T> s;
    int n;
    SegmentTree(int n_ = 0, T def = unit) {
        int log = 1; 
        while ((1 << log) < n_) log++;
        n = 1 << log;
        s = vector<T>(n * 2, def);
    }
    // s[i] = x;
    void update(int i, T x) {
        i += n;
        s[i] = x;
        while (i >>= 1) {
            s[i] = f(s[2 * i], s[2 * i + 1]);
        }
    }
    // s[i] = f(s[i], x);
    void apply(int i, T x) {
        i += n;
        s[i] = f(s[i], x);
        while (i >>= 1) {
            s[i] = f(s[2 * i], s[2 * i + 1]);
        }
    }
    // 区間取得: [b, e)
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};