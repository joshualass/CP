#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> a(1, 0);
    set<int> s;
    s.insert(0);
    for(int i = 0; i < 500; i++) {
        int x = a.back();
        vector<int> res;
        for(int j = 0; j < 1 << 10; j++) {
            int t = x ^ j;
            if(__builtin_popcount(t) % 2 == 0) {
                res.push_back(t);
            }
        }
        // cout << "res : " << res << '\n';
        sort(res.begin(), res.end());
        for(int y : res) {
            if(s.count(y) == 0) {
                s.insert(y);
                a.push_back(y);
                break;
            }
        }
        
    }

    // cout << "a : " << a << '\n';

    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        int q; cin >> q;
        cout << bitset<10>(a[q]) << '\n';
    }

    return 0;
}
