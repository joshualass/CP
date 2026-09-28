#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

//slowest solves of all time; handle more work on paper and don't be as washed, ig
//can optimize log n factor but not necessary :yawn:

const int debug = 0;
const int ddebug = 0;


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

ll solve(int n, vector<int> a) {
    vector<int> p(n), rp(n);
    for(int i = 0; i < n; i++) {
        int x = a[i];
        x--;
        p[i] = x;
        rp[x] = i;
    }

    vector<array<int,2>> mx(n); //stores suffix maxes, {val, idx}
    for(int i = n - 1; i >= 0; i--) {
        mx[i] = {p[i], i};
        if(i < n - 1) {
            mx[i] = max(mx[i], mx[i+1]);
        }
    }

    vector<int> r(n, -1); // -1 -> undefined, indices stored
    vector<int> st;
    for(int i = n - 1; i >= 0; i--) {
        int x = p[i];
        while(!st.empty() && x > st.back()) st.pop_back();
        if(!st.empty()) {
            r[i] = rp[st.back()];
        }
        st.push_back(x);
    }

    vector<int> mid(n, -1); //compute the mid values if they exist
    st.clear();
    vector<int> shooters(n), shoothere(n);
    int shootcnt = 0;

    auto upd_shooter = [&](int i, int delta) -> void {
        if(r[i] != -1) {
            if(shooters[r[i]]) shootcnt--;
            shooters[r[i]] += delta;
            if(shooters[r[i]]) shootcnt++;
        }
    };

    for(int i = 0; i < n; i++) {
        // cout << "bm i : " << i << endl;
        int x = p[i];
        while(!st.empty() && -x < st.back()) {
            upd_shooter(rp[-st.back()], -1);
            st.pop_back();
        }
        int ub = mx[i][0];
        auto it = upper_bound(st.begin(), st.end(), -ub);
        if(it != st.end()) {
            int test = *it;
            // cout << "test : " << test << endl;
            int test_i = rp[-test];
            if(r[test_i] != r[i]) {
                assert(r[i] != -1 && r[test_i] != -1);
                mid[i] = test_i;
            }
        }
        int t = shootcnt;
        if(r[i] != -1) {
            if(shooters[r[i]]) t--;
            if(r[r[i]] != -1) {
                if(shooters[r[r[i]]]) t--;
            }
        }

        shoothere[i] = t;
        st.push_back(-x);
        upd_shooter(i, 1);
    }

    // cout << "mx : " << mx << endl;
    // cout << "r : " << r << endl;
    // cout << "mid : " << mid << endl;
    // cout << "shoothere : " << shoothere << endl;

    vector<ll> d(n);
    for(int val = n - 1; val >= 0; val--) {
        ll i = rp[val];
        // cout << "i : " << i << endl;
        if(r[i] == -1) {
            // cout << "no r" <<  endl;
            d[i] = i;
        } else if(mid[i] == -1) {
            d[i] = d[r[i]] + (mx[i][1] - ((i + 1)));
            // cout << "no mid" << endl;
        } else {
            // cout << "ttfang case" << endl;
            assert(r[mid[i]] != -1 && r[r[i]] != -1);
            d[i] = d[mid[i]] + mx[i][1] + 1 - (1 + (i - mid[i]) * 2) - mid[i] - (r[i] - i + 1) - shoothere[i];
            if(r[mid[i]] > r[r[i]]) { 
                // d[i] = d[mid[i]] + (mx[i][1] + 1 - ((i + 1) + (r[r[i]] - i)));
                // cout << "rri" << endl;
                // d[i]--;
                //for each guy, more than one of these!

            } else {
                // cout << "ri" << endl;
                // d[i] = d[mid[i]] + (mx[i][1] + 1 - ((i + 1) + (r[i] - i)));
            }
        }
    }

    if(ddebug) {
        cout << "fast d : " << d << endl;
    }

    return accumulate(d.begin(), d.end(), 0LL);

}

ll solve_slow(int n, vector<int> a) {
    for(int &x : a) x--;
    vector<ll> d(n);
    
    for(int i = 0; i < n; i++) {
        queue<array<int,2>> q;
        q.push({i, 0});
        vector<int> vis(n);
        ll here = 0;
        while(!q.empty()) {
            auto [x, dis] = q.front();
            q.pop();
            if(vis[x]) continue;
            here += dis;
            vis[x] = 1;
            for(int i = x - 1; i >= 0; i--) q.push({i, dis + 1});
            for(int i = x + 1; i < n; i++) {
                if(a[i] > a[x]) {
                    q.push({i, dis + 1});
                    break;
                }
            }
        }
        d[i] = here;
    }

    if(ddebug) {
        cout << "slow d : " << d << endl;
    }

    return accumulate(d.begin(), d.end(), 0LL);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        int casi; cin >> casi;
        for(int i = 0; i < casi; i++) {
            int n; cin >> n;
            vector<int> p(n);
            for(int &x : p) cin >> x;
            cout << solve(n, p) << '\n';

            if(ddebug) {
                solve_slow(n, p);
            }
            
        }
    } else {

        for(int n = 1; n <= 10; n++) {
            vector<int> a(n);
            iota(a.begin(), a.end(), 1);
            while(1) {
                ll res_fast = solve(n, a);
                ll res_slow = solve_slow(n, a);
                if(res_fast != res_slow) {
                    cout << "fast : " << res_fast << endl;
                    cout << "slow : " << res_slow << endl;
                    cout << n << endl;
                    cout << a << endl;
                    assert(0);
                }
                if(!next_permutation(a.begin(), a.end())) break;
            }
        }

        cout << "all tests ok!" << endl;
    }


    return 0;
}