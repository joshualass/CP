#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int debug = 0;

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
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}



int n;
vector<int> a;

//yay oop
struct ds {

    int mx;
    priority_queue<array<int,2>> pq;
    map<int,pair<array<int,2>,vector<int>>> m; // {{r, zeros}, cnts}

    ds(int mx): mx(mx) {
        init();
    }

    void init() {
        int l = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] >= mx) {
                add(l, i);
                l = i + 1;
            }
        }
        add(l, n);
    }

    void add(int l, int r) {
        if(r - l >= mx) {
            vector<int> cnts(mx);
            int zero = mx;
            for(int i = l; i < r; i++) {
                if(cnts[a[i]] == 0) zero--;
                cnts[a[i]]++;
            }
            m[l] = {{r, zero}, cnts};
            if(zero == 0) {
                pq.push({r - l, l});
            }
        }
    }

    void remove(map<int,pair<array<int,2>,vector<int>>>::iterator it, int val) {
        it->second.second[val]--;
        if(it->second.second[val] == 0) {
            it->second.first[1]++;
        }
    }

    void add(map<int,pair<array<int,2>,vector<int>>>::iterator it, int val) {
        if(it->second.second[val] == 0) {
            it->second.first[1]--;
        }
        it->second.second[val]++;
        if(it->second.first[1] == 0) {
            pq.push({it->second.first[0] - it->first, it->first});
        }
    }

    void update(int i, int x) {
        auto it = m.upper_bound(i);
        if(it != m.begin()) {
            it--;
            int l = it->first;
            int r = it->second.first[0];
            if(i < r) {
                if(x < mx) {
                    // cout << "under!" << endl;
                    remove(it, a[i]);
                    add(it, x);
                } else {
                    int llen = i - l, rlen = r - i - 1;
                    if(llen > rlen) {
                        for(int j = i; j < r; j++) {
                            remove(it, a[j]);
                        }
                        add(i + 1, r);
                        it->second.first[0] = i;
                        pq.push({i - l, l});
                    } else {
                        for(int j = l; j <= i; j++) {
                            remove(it, a[j]);
                        }
                        m[i+1];
                        swap(m[l], m[i+1]);
                        m.erase(l);
                        pq.push({r - (i + 1), i + 1});

                        add(l, i);
                    }
                }
            }
        }
    }

    int query() {
        while(!pq.empty()) {
            auto [len, l] = pq.top();
            if(m.count(l) && m[l].first[0] - l == len && m[l].first[1] == 0) {
                break;
            }
            pq.pop();
        }
        if(!pq.empty()) return pq.top()[0];
        return 0;
    }
};

int solve_slow() {
    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j <= n; j++) {
            vector<int> cur;
            int o = 0;
            for(int k = i; k < j; k++) {
                cur.push_back(a[k]);
                o |= a[k];
            }
            int mex = 0;
            while(count(cur.begin(), cur.end(), mex)) mex++;
            if(mex - o == 1) res = max(res, j - i);
        }
    }
    return res;
}

void solve() {

    int q; 
    if(debug == 0) {
        cin >> n >> q;
    } else {
        n = 10;
        q = 10;
    }
    
    a.resize(n);
    if(debug == 0) {
        for(int &x : a) cin >> x;
    } else {
        a.assign(n, 0);
    }

    vector<ds> b;
    for(int i = 1; i <= n; i *= 2) {
        b.push_back(ds(i));
    }

    vector<array<int,2>> qs;

    for(int qq = 0; qq < q; qq++) {
        int i, x; 
        if(debug == 0) {
            cin >> i >> x;
            i--;
        } else {
            i = rng() % n;
            x = 1;
        }

        int res = 0;
        // cout << "mih qq : " << qq << endl;
        // cout << "a : " << a << endl;
        for(int j = 0; j < sz(b); j++) {
            // cout << "qq : " << qq << " pre  j : " << j << " map : " << b[j].m << endl;
            b[j].update(i, a[i] + x);
            res = max(res, b[j].query());
            // cout << "qq : " << qq << " post j : " << j << " map : " << b[j].m << endl;
        }
        a[i] += x;

        if(debug) {
            int res_slow = solve_slow();
            qs.push_back({i, x});
            if(res != res_slow) {
                cout << "a : " << a << endl;
                cout << "qs : " << qs << endl;
                cout << "fast : " << res << " slow : " << res_slow << endl;
                assert(0);
            }
        }

        cout << res << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        int casi; cin >> casi;
        while(casi-->0) solve();
    } else {
        for(int i = 0; i < 6767; i++) {
            solve();
        }
    }


    return 0;
}