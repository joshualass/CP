#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

void solve() {
    
    int n; cin >> n;
    vector<array<ll,2>> b(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i][0];
        b[i][1] = i;
    }

    sort(b.begin(), b.end());

    // cout << "b : " << b << endl;

    vector<ll> res(n);
    int prev = 0;
    int ok = 1;

    ll prev_val = 0;
    ll cur = 0;

    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(b[i][0]) {
                ok = 0;
                break;
            }
        } else {
            if(b[i][0] != b[i-1][0]) {
                int cnt = i - prev;
                ll rem = b[i][0] - cur;
                if(rem % cnt == 0 && rem / cnt > prev_val) {
                    ll val = rem / cnt;
                    // cout << "i : " << i << " val : " << val << endl;
                    for(int j = prev; j < i; j++) {
                        res[b[j][1]] = val;
                    }
                    prev_val = val;
                    cur += val * cnt;
                    prev = i;
                } else {
                    ok = 0;
                }

            }
        }
    }

    for(int j = prev; j < n; j++) {
        res[b[j][1]] = prev_val + 1;
    }

    if(ok) {
        cout << res << '\n';
    } else {
        cout << "-1\n";
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