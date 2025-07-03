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

    int n; cin >> n;

    vector<int> a(n);

    auto get_distinct = [&](int l, int r) -> int {
        set<int> s;
        for(int i = l; i < r; i++) s.insert(a[i]);
        return s.size();
    };

    int id = 0;

    // cout << "upd a : " << a << '\n';

    for(int i = 1; i < n; i++) {
        int l = -1, r = i - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            // cout << "l : " << l << " r : " << r << " m : " << m << '\n';
            cout << "? " << m + 1 << " " << i + 1 << endl;
            char trash; cin >> trash;
            int res; cin >> res;
            int dist = get_distinct(m, i);
            if(dist == res) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if(l == -1) {
            a[i] = ++id;
        } else {
            a[i] = a[l];
        }
    
        // cout << "upd a : " << a << '\n';

    }

    vector<int> res;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[j] == i) {
                res.push_back(j);
            }
        }
    }

    cout << "!";
    for(int x : res) cout << " " << x + 1;
    cout << endl;

    return 0;
}
