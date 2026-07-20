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

int invcnt(vector<int> &a) {
    int res = 0;
    for(int i = 0; i < sz(a); i++) {
        for(int j = i + 1; j < sz(a); j++) {
            res += a[i] > a[j];
        }
    }
    return res;
}

void solve() {
    
    int n; cin >> n;
    vector<int> p(n);
    for(int &x : p) {
        cin >> x;
        x--;
    }

    if(n % 2 == 0 && invcnt(p) % 2) {
        cout << "-1\n";
        return;
    }

    // cout << "mih : " << p << endl;

    vector<int> res;
    
    auto add_op = [&](int idx) -> void {
        assert(0 <= idx && idx + 1 < n);
        res.push_back(idx);
        rotate(p.begin(), p.begin() + idx, p.begin() + idx + 1);
        rotate(p.begin() + idx + 1, p.begin() + idx + 2, p.end());
    };

    for(int i = 0; i + 2 < n; i++) {
        int idx = -1;
        for(int j = 0; j < n; j++) {
            if(p[j] == i) idx = j;
        }

        // cout << "i : " << i << " idx : " << idx << endl;
        if(idx != n - 1) {
            if(idx == 0) {
                add_op(1);
                add_op(0);
                add_op(n - 2);
            } else {
                add_op(idx - 1);
            }
        }

        if(i == 0 && invcnt(p) % 2) {
            add_op(n - 2);
        }

        // cout << "i : " << i << " " << " p : " << p << endl;
    }

    add_op(0);
    for(int i = 0; i < n - 2; i++) {
        add_op(n - 2);
    }

    assert(is_sorted(p.begin(), p.end()));

    cout << sz(res) << '\n';
    for(int i = 0; i < sz(res); i++) {
        cout << res[i] + 1 << " \n"[i == sz(res) - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}