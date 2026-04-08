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

const int MAXN = 1e6;
ll pre[2][MAXN], suf[2][MAXN], c[MAXN];
vector<array<ll,2>> sts[MAXN];

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    int type = 1;

    {
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
            pre[0][i] = cnt;
        }
        // cout << "res : " << res << endl;
    }

    {
        for(int i = 0; i < n; i++) c[i] = 0;
        for(int i = 0; i < n; i++) while(sz(sts[i])) sts[i].pop_back();
        stack<array<ll,3>> st;
        stack<array<ll,2>> s;
        ll cnt = 0;

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
                while(!sts[idx].empty() && sts[idx].back()[0] > a[i]) {
                    auto [th, tl] = sts[idx].back();
                    sts[idx].pop_back();
                    c[idx] -= (th - a[idx]) * tl;
                    nx[1] += tl;
                }

                sts[idx].push_back(nx);
                c[idx] += (nx[0] - a[idx]) * nx[1];
                
                ll prev = s.size() ? s.top()[1] : 0;
                s.push({c[idx], max(c[idx], prev)});
            }

            st.push(cur);
            
            reverse(popped.begin(), popped.end());
            
            for(auto [th, tl] : popped) {
                sts[i].push_back({th, tl});
                c[i] += (th - a[i]) * tl;
            }
            
            ll best_add = 0;
            if(!s.empty()) best_add = s.top()[1];
            
            pre[1][i] = cnt + best_add;

            ll prev = s.size() ? s.top()[1] : 0;
            // s.insert({c[i], i});
            s.push({c[i], max(c[i], prev)});
        }
        // cout << "res : " << res << endl;
    }

    reverse(a.begin(), a.end());

    {
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
            suf[0][n-i-1] = cnt;
        }
        // cout << "res : " << res << endl;
    }

    {
        for(int i = 0; i < n; i++) c[i] = 0;
        for(int i = 0; i < n; i++) while(sz(sts[i])) sts[i].pop_back();
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
                while(!sts[idx].empty() && sts[idx].back()[0] > a[i]) {
                    auto [th, tl] = sts[idx].back();
                    sts[idx].pop_back();
                    c[idx] -= (th - a[idx]) * tl;
                    nx[1] += tl;
                }

                sts[idx].push_back(nx);
                c[idx] += (nx[0] - a[idx]) * nx[1];
                
                ll prev = s.size() ? s.top()[1] : 0;
                s.push({c[idx], max(c[idx], prev)});
            }

            st.push(cur);
            
            reverse(popped.begin(), popped.end());
            
            for(auto [th, tl] : popped) {
                sts[i].push_back({th, tl});
                c[i] += (th - a[i]) * tl;
            }
            
            ll best_add = 0;
            if(!s.empty()) best_add = s.top()[1];
            
            suf[1][n-i-1] = cnt + best_add;

            ll prev = s.size() ? s.top()[1] : 0;
            // s.insert({c[i], i});
            s.push({c[i], max(c[i], prev)});
        }
        // cout << "res : " << res << endl;
    }

    reverse(a.begin(), a.end());

    ll res = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                if(j + k <= 1) {
                    res = max(res, pre[j][i] + suf[k][i] - a[i]);
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