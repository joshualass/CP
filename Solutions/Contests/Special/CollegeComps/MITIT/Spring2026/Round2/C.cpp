#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const ll inf = 1e9;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    auto work0 = [&]() -> vector<ll> {
        // cout << "work0 a : " << a << endl;
        stack<array<ll,2>> st;
        vector<ll> res(n);
        ll cnt = 0;
        for(int i = 0; i < n; i++) {
            array<ll,2> cur = {a[i], 1};
            while(!st.empty() && st.top()[0] >= cur[0]) {
                auto [th, tl] = st.top();
                st.pop();
                cnt -= th * tl;
                cur[1] += tl;
            }
            cnt += cur[0] * cur[1];
            st.push(cur);
            res[i] = cnt;
        }
        // cout << "res : " << res << endl;
        return res;
    };

    auto work1 = [&](int type) -> vector<ll> {
        if(type == 0) {
            vector<ll> res = work0();
            for(int idx = 0; idx < n; idx++) {
                ll t = inf;
                swap(a[idx], t);

                stack<array<ll,2>> st;
                ll cnt = 0;

                for(int i = 0; i < n; i++) {
                    array<ll,2> cur = {a[i], 1};
                    while(!st.empty() && st.top()[0] >= cur[0]) {
                        auto [th, tl] = st.top();
                        st.pop();
                        cnt -= th * tl;
                        cur[1] += tl;
                    }
                    cnt += cur[0] * cur[1];
                    st.push(cur);

                    if(i > idx) {
                        res[i] = max(res[i], cnt);
                    }
                }
                swap(a[idx], t);
            }
            return res;
        } else {
            // cout << "work1 a : " << a << endl;
            vector<ll> c(n), res(n);
            vector<stack<array<ll,2>>> sts(n);
            stack<array<ll,3>> st;
            ll cnt = 0;
            stack<array<ll,2>> s;
    
            for(int i = 0; i < n; i++) {
                // cout << "i : " << i << endl;
                array<ll,3> cur = {a[i], 1, i};

                vector<array<ll,2>> popped;
                popped.push_back({inf, 1});

                while(!st.empty() && st.top()[0] >= cur[0]) {
                    auto [th, tl, idx] = st.top();
                    st.pop();
                    s.pop();

                    popped.push_back({th, tl});

                    cnt -= th * tl;
                    cur[1] += tl;
    
                }
    
                cnt += cur[0] * cur[1];
                
                //update c of st top
                if(!st.empty()) {
                    int idx = st.top()[2];
    
                    // cout << "idx : " << idx << endl;
    
                    // assert(s.count({c[idx], idx}));
                    // s.erase({c[idx], idx});

                    s.pop();
    
                    array<ll,2> nx = {a[i], 0};
                    while(!sts[idx].empty() && sts[idx].top()[0] > a[i]) {
                        auto [th, tl] = sts[idx].top();
                        sts[idx].pop();
                        c[idx] -= (th - a[idx]) * tl;
                        nx[1] += tl;
                    }

                    sts[idx].push(nx);
                    c[idx] += (nx[0] - a[idx]) * nx[1];
                    
                    ll prev = s.size() ? s.top()[1] : 0;
                    s.push({c[idx], max(c[idx], prev)});
                }
    
                st.push(cur);
                
                reverse(popped.begin(), popped.end());
                
                for(auto [th, tl] : popped) {
                    sts[i].push({th, tl});
                    c[i] += (th - a[i]) * tl;
                }
                
                ll best_add = 0;
                if(!s.empty()) best_add = s.top()[1];
                
                res[i] = cnt + best_add;

                ll prev = s.size() ? s.top()[1] : 0;
                // s.insert({c[i], i});
                s.push({c[i], max(c[i], prev)});
            }
            // cout << "res : " << res << endl;
            return res;
        }
    };

    // for(int i = 0; i < 100000; i++) {
    //     a.resize(n);
    //     for(int j = 0; j < n; j++) a[j] = rng() % n + 1;
    //     cout << "testing a : " << a << endl;
    //     if(work1(0) != work1(1)) {
    //         cout << "fast : " << work1(0) << endl;
    //         cout << "slow : " << work1(1) << endl;
    //         assert(0);
    //     }
    // }

    int type = 1;

    vector<vector<ll>> p(2), s(2);
    p[0] = work0();
    p[1] = work1(type);

    reverse(a.begin(), a.end());

    s[0] = work0();
    s[1] = work1(type);

    reverse(a.begin(), a.end());
    for(int i = 0; i < 2; i++) reverse(s[i].begin(), s[i].end());

    ll res = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                if(j + k <= 1) {
                    res = max(res, p[j][i] + s[k][i] - a[i]);
                }
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}