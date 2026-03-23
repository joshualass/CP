#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "{";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << ", ";
    return os;
}

template <typename T>
void printS(stack<T> x) {
    cout << "stack: ";
    while(x.size()) {
        cout << x.top() << ' ';
        x.pop();
    }
    cout << endl;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

int debug = 5;

const int lim = 30;
const int ms = 4;
const ll inf = 1e18;

struct Tree {
    typedef vector<array<ll,2>> T;
    T base = {};
    vector<T> v;
    int n, size;

    array<ll,2> norm(ll k, ll v) {
        assert(v);
        ll av = abs(v);
        int tz = __builtin_ctzll(av);
        av >>= tz;
        k += tz;
        if(v < 0) av *= -1;
        return {k, av};
    }

    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        // cout << "f call begin" << endl;
        vector<array<ll,2>> res;
        int ai = sz(a) - 1, bi = sz(b) - 1;
        stack<array<ll,2>> st;
        while(ai >= 0 || bi >= 0) {
            // cout << "ai : " << ai << " bi : " << bi << endl;
            if(ai >= 0 && (bi == -1 || a[ai][0] < b[bi][0])) {
                // cout << "pusha" << endl;
                st.push(a[ai--]);
            } else {
                // cout << "pushb" << endl;
                st.push(b[bi--]);
            }
        }
        auto cop = st;
        int cnt = 0;
        // cout << "BEGIN WHILE" << endl;
        while(sz(st)) {
            // cout << "state of res : " << res << endl;
            // printS(st);

            auto [k, v] = st.top();
            st.pop();
            // cnt++;
            // if(cnt > 10) {
            //     cout << "likely inf loop" << endl;
            //     cout << "a : " << a << endl;
            //     cout << "b : " << b << endl;
            //     printS(cop);    
            //     assert(0);
            // }
            if(res.empty()) {
                res.push_back({k, v});
            } else {
                if(k > res.back()[0]) {
                    swap(res.back()[0], k);
                    swap(res.back()[1], v);
                    sort(res.rbegin(), res.rend());
                }
                // if(!(res.back()[0] >= k)) {
                //     cout << "bad res cur : " << res << " k : " << k << endl;
                //     cout << "a : " << a << endl;
                //     cout << "b : " << b << endl;
                //     printS(cop);
                // }
                assert(res.back()[0] >= k);
                int d = res.back()[0] - k;
                if(d < lim) {
                    ll s = (res.back()[1]) * (1LL << d) + v;
                    // cout << "s : " << s << endl;
                    if(s) {
                        int shift = max(0, 64 - (lim + __builtin_clzll(abs(s))));
                        ll big = (abs(s) >> shift) << shift;
                        ll small = abs(s) - big;
                        // cout << "big : " << big << " small : " << small << endl;
                        if(s < 0) {
                            big *= -1;
                            small *= -1;
                        }

                        if(norm(k, big) == res.back()) {
                            ll bad = (1LL << lim) - 1;
                            if(small == bad) {
                                st.push({k, -1});
                                st.push({k+30,1});
                            } else if(small == -bad) {
                                st.push({k,1});
                                st.push({k+30,-1});
                            } else {
                                res.push_back({k, v});
                            }
                        } else {
                            res.pop_back();
                            if(small) st.push(norm(k, small));
                            if(big) st.push(norm(k, big));
                        }
                    } else {
                        res.pop_back();
                    }
                } else {
                    res.push_back({k, v});
                    continue;
                }
            }
        }

        // cout << "resulting res : " << res << endl;
        
        ll sum = 0;
        // for(auto [k, v] : a) sum += v * (1LL << k);
        // for(auto [k, v] : b) sum += v * (1LL << k);
        // for(auto [k, v] : res) sum -= v * (1LL << k);
        if(sz(res) > ms || sum != 0) {
            cout << "resulting sum is different" << endl;
            cout << "a : " << a << endl;
            cout << "b : " << b << endl;
            cout << "res : " << res << endl;
            assert(0);
        }
        
        while(sz(res) > ms) res.pop_back();
        // cout << "final res : " << res << endl;
        return res;
    }

    Tree(int n, T def) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

vector<array<ll,2>> get_map(int i, int val) {
    return val ? vector<array<ll,2>>{{i, val}} : vector<array<ll,2>>{};
}

int sgnum(vector<array<ll,2>> res) {
    if(res.empty()) return 0;
    ll num = res[0][1];
    if(num > 0) return 1;
    if(num < 0) return -1;
    return 0;
}

void solve() {
    
    int n, q; 
    if(debug == 2) {
        n = 500000, q = 500000;
    } else if(debug == 5) {
        n = 20000, q = 1;
    } else {
        cin >> n >> q;
    }
    Tree tree(n, {});
    int ok = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int x;
        if(debug == 2) {
            x = 1000000000;
        } else if(debug == 5) {
            if(i == 0) {
                x = 999999997;
            } else if(i == n - 1) {
                x = -499999998;
            } else {
                x = 499999998;
            }
        } else {
            cin >> x;
        }
        if(i == 0 && x == 499999998) ok = 1;
        // cout << "i : " << i << " map : " << get_map(i, x) << endl;
        tree.update(i, get_map(i, x));
        a[i] = x;
    }

    if(debug == 4) {
        for(int i = 1; tree.v.size() >= 1 << i; i++) {
            for(int j = 1 << (i - 1); 1 << i > j; j++) {
                // os << "i : " << i << " j : " << j << ' ';
                cout << '[' << tree.v[j] << "] ";
            }
            cout << endl;
        }
    }

    int out_cnt = 0;
    for(int qq = 0; qq < q; qq++) {
        int type;
        if(debug == 2) {
            type = (qq & 1) + 1;
        } else {
            cin >> type;
        }
        if(debug == 5) type = 2;
        cout << "qq : " << qq << " t : " << type << endl;
        if(type == 1) {
            int i, val; 
            if(debug == 2) {
                i = qq, val = 1000000000 * (qq % 2 == 0 ? 1 : -1);
            } else {
                cin >> i >> val;
                i--;    
            }
            a[i] = val;
            tree.update(i, get_map(i, val));
        } else {
            int l, r; 
            if(debug == 2 || debug == 5) {
                l = 0, r = n;
            } else {
                cin >> l >> r;
                l--;
            }
            cout << "mih l : " << l << " r : " << r << endl;
            out_cnt++;
            if(ok && out_cnt == 100000) {
                cout << "L"<<l<<"R"<<r;
                auto res = tree.query(l,r);
                cout << "R";
                for(auto x : res) cout << "{" << x[0]<<","<<x[1]<<"}";
                cout << '\n';
                // for(int i = l; i < r; i++)cout<<a[i]<<",";
                // cout << '\n';
            }
            auto res = tree.query(l, r);
            cout << "res : " << res << endl;
            cout << sgnum(res) << '\n';
        }
    }

}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    clock_t tStart = clock();

    
    if(debug) {
        if(debug == 1) {
            Tree tree(0, {});
            vector<array<ll,2>> a = {
                {19967, -1}
            }, b = {
                {19937, 1073741823}
            };
            auto res = tree.f(a, b);
        } else if(debug == 2 || 5) {
            solve();
        } else if(debug == 3) {
            int n = 10;
            Tree tree(n, {});
            vector<ll> a(n);
            for(int i = 0; i < 1000000; i++) {
                int type = rng() & 1;
                if(type == 0) {
                    int i = rng() % n, val = rng() % 2;
                    if(rng() & 1) val *= -1;
                    a[i] = val;
                    tree.update(i, get_map(i, val));
                } else {
                    int l = rng() % n, r = rng() % n;
                    if(l > r) swap(l, r);
                    r++;
                    int res_fast = sgnum(tree.query(l, r));
                    ll s = 0, mul = 0;
                    for(int i = r - 1; i >= l; i--) {
                        s = max(-inf, min(s * 2 + a[i], inf));
                    }
                    int res_slow = sgnum(vector<array<ll,2>>{{0LL, s}});
                    if(res_fast != res_slow) {
                        cout << "anomaly detected!" << endl;
                        cout << "a : " << a << endl;
                        cout << "l : " << l << " r : " << r << endl;
                        cout << "fast : " << res_fast << endl;
                        cout << "slow : " << res_slow << endl;
                        return 0;
                    }
                    cout << "fast : " << res_fast << " slow : " << res_slow << '\n';
                }
            }
            cout << "all g" << endl;
        } else if(debug == 4) {
            int casi; cin >> casi;
            while(casi-->0) solve();
        }
    } else {
        int casi; cin >> casi;
        while(casi-->0) solve();
    }
    
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    return 0;
}