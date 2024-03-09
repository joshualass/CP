#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n, k, x; cin >> n >> k >> x;
    bool ok = 1;
    set<int> s;
    for(int i = 0; i <= n; i++) s.insert(i);
    vector<vector<int>> ss;
    while(ss.size() != k) {
        if(s.empty()) {
            ok = 0;
            break;
        }
        int hi = (*--s.end());
        s.erase(hi);
        int c = x ^ hi;
        if(s.count(c)) {
            if(c != 0) {
                ss.push_back({hi,c});
            } else {
                ss.push_back({hi});
            }
            s.erase(c);
        } else {
            cout << "no workie hi : " << hi << '\n';
            ok = 0;
            break;
        }
    }
    s.erase(0);
    cout << "ss\n" << ss;
    if(ok) {
        for(int x : s) ss.back().push_back(x);
        for(vector<int> v : ss) {
            int a = 0;
            for(int y : v) a ^= y;
            if(a != x) ok = 0;
        }
        if(ok) {
            cout << "YES\n";
            for(vector<int> v : ss) {
                cout << v.size() << " ";
                sort(v.begin(), v.end());
                for(int i = 0; i < v.size(); i++) {
                    cout << v[i] << " \n"[i == v.size() - 1];
                }
            }
            return;
        }
    }
    cout << "NO\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}