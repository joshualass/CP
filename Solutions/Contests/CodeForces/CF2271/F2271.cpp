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

void solve() {
    
    auto check = [](vector<int> a) -> int {
        int n = sz(a);
        vector<int> p(n + 1);
        vector<int> st;
        for(int i = 0; i < n; i++) {
            while(sz(st) && a[i] > a[st.back()]) st.pop_back();
            if(sz(st) && a[i] == a[st.back()]) {
                p[st.back()]++;
                p[i + 1]--;
            }
            st.push_back(i);
        }
        int cur = 0;
        for(int i = 0; i < n; i++) {
            cur += p[i];
            if(cur == 0) return i + 1;
        }
        // cout << "a : " << a << " is 0" << endl;
        return 0;
    };

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<array<int,2>> res;
    if(check(a) == 0) {
        // cout << "0!" << endl;
        //0 ops :)
    } else {

        int mx = *max_element(a.begin(), a.end());

        auto b = a;
        b[0] = mx;
        if(check(b) == 0) {
            res = {{0, mx}};
        } else {
            b = a;
            b[n-1] = mx;
            if(check(b) == 0) {
                res = {{n - 1, mx}};
            } else {
                b = a;
                int mxcnt = count(a.begin(), a.end(), mx);
                if(mxcnt == 1) {
                    auto b = a;
                    int mx_idx = -1;
                    for(int i = 0; i < n; i++) {
                        if(b[i] == mx) {
                            mx_idx = i;
                        }
                    }
                    b[mx_idx] = 1;
                    if(check(b) == 0) {
                        res = {{mx_idx, 1}};
                    } else {
                        int fb = check(b);  

                        b[mx_idx] = b[fb];
                        if(check(b) == 0) {
                            res = {{mx_idx, b[fb]}};
                        } else {
                            res = {{0, mx}, {n - 1, mx}};
                        }
                    }
                } else {
                    res = {{0, mx}, {n - 1, mx}};
                }
            }
        }
    }

    cout << sz(res) << '\n';
    for(auto [i, x] : res) {
        cout << i + 1 << " " << x << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}