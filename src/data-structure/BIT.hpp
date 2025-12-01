struct BIT {
    vector<ll> a;
    BIT(ll n) : a(n + 1) {}
    // A[i] += x
    void add(ll i, ll x){
        i++;
        while(i < (int)a.size()){
            a[i] += x;
            i += i & -i;
        }
    }
    // sum of A[0, r)
    ll sum(ll r) {
        ll s = 0;
        while(r){
            s += a[r];
            r -= r & -r;
        }
        return s;
    }
    // sum of A[l, r)
    ll sum(ll l, ll r){  
        return sum(r) - sum(l);
    }
};
