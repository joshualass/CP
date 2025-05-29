#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
onlinegdb being slow. solve this later*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        if(a[0] > b[0]) {
            return a;
        }
        return b;
    }
    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));
        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }
    }
    //[l,r) always. 
    T query(int l, int r) {
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

#include <ext/pb_ds/assoc_container.hpp> //0-indexed
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
/*
order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero).
*/
template <class T>
using os =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    vector<ll> h(n), a(n);
    for(ll &x : h) cin >> x;
    for(ll &x : a) cin >> x;

    vector<array<ll,2>> d(n);
    vector<ll> p(n);
    
    for(int i = 0; i < n; i++) {
        ll dif = (h[i] > a[i] ? h[i] - a[i] : (h[i] - a[i]) * k);
        p[i] = dif + (i ? p[i-1] : 0);
        d[i] = {dif, i};
    }
    
    cout << "h : " << h << '\n';
    cout << "a : " << a << '\n';
    cout << "d : " << d << '\n';

    sparse<array<ll,2>> rmq(d);
    
    auto get_p = [&](int l, int r) -> ll {
        return p[r] - (l ? p[l-1] : 0);
    };

    auto add = [&](int i, os<array<ll,2>> &ps, os<array<ll,2>> &ss) -> void {
        ps.insert({get_p(0, i), i});
        ss.insert({get_p(i, n - 1), i}); 
    };
    
    auto rem = [&](int i, os<array<ll,2>> &ps, os<array<ll,2>> &ss) -> void {
        ps.erase({get_p(0, i), i});
        ss.erase({get_p(i, n - 1), i});
    };
    
    ll res = 0;
    
    auto dfs = [&](auto self, int l, int r, os<array<ll,2>> &ps, os<array<ll,2>> &ss) -> void {
        if(l > r) return;
        auto [val, mid] = rmq.query(l, r);
        
        // cout << "l : " << l << " r : " << r << " ps sz : " << ps.size() << " ss sz : " << ss.size() << endl;
        
        ll cnt_here = 0;
        
        int lc = mid - l + 1, rc = r - mid + 1;
        if(lc < rc) { //left side is smaller, iterate through them all
            //remove all things up to but excluding mid when calculating things
            for(int i = l; i < mid; i++) rem(i, ps, ss);
            
            ll offset = get_p(0, mid);
            for(int i = l; i <= mid; i++) {
                ll score = get_p(i, mid - 1) - abs((h[mid] - a[mid]) * k);
                ll qv = -score + offset;
                ll cnt = ps.size() - ps.order_of_key({qv, -1});
                if(l == 0 && r == 3) {
                    cout << "i : " << i << " score : " << score << " qv : " << qv << " cnt : " << cnt << endl;
                }
                res += cnt;
                cnt_here += cnt;
            }
            
            rem(mid, ps, ss);
            
            os<array<ll,2>> lps, lss;
            for(int i = l; i < mid; i++) {
                add(i, lps, lss);
            }
            
            self(self, l, mid - 1, lps, lss);
            self(self, mid + 1, r, ps, ss);
            
        } else {
            for(int i = r; i > mid; i--) rem(i, ps, ss);
            
            ll offset = get_p(mid, n - 1);
            
            for(int i = r; i >= mid; i--) {
                ll score = get_p(mid + 1, i) - abs((h[mid] - a[mid]) * k);
                ll qv = -score + offset;
                ll cnt = ss.size() - ss.order_of_key({qv, -1});
                if(l == 0 && r == 3) {
                    cout << "i : " << i << " score : " << score << " qv : " << qv << " cnt : " << cnt << endl;
                }
                res += cnt;
                cnt_here += cnt;
            }
            
            rem(mid, ps, ss);
            os<array<ll,2>> rps, rss;
            for(int i = r; i > mid; i--) {
                add(i, rps, rss);
            }
            
            self(self, l, mid - 1, ps, ss);
            self(self, mid + 1, r, rps, rss);
        }
        
        cout << "l : " << l << " r : " << r << " mid : " << mid << endl;
        cout << "cnt : " << cnt_here << endl;
        
    };
    
    os<array<ll,2>> ips, iss;
    for(int i = 0; i < n; i++) {
        add(i, ips, iss);
    }
    
    dfs(dfs, 0, n - 1, ips, iss);
    
    cout << res << '\n';

    return 0;
}
