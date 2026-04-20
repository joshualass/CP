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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<array<int,3>> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    sort(a.begin(), a.end());

    vector<array<int,3>> res;
    map<int,array<int,2>> m; // {y, {x, id}}

    for(int i = 0; i < n; i++) {
        auto [x, y, id] = a[i];
        // cout << "x : " << x << " y : " << y << " id : " << id << endl;
        // cout << "map : " << m << endl;
        auto it = m.lower_bound(y);
        if(it != m.end() && it != m.begin()) {
            auto prev = it;
            prev--;
            // cout << "add up down triple : " << (array<int,3>{prev->second[1], it->second[1], id}) << endl;
            res.push_back({prev->second[1], it->second[1], id});
        }   
        while(it != m.end()) {
            auto nx = it;
            nx++;
            if(nx == m.end()) break;
            if(nx->second[0] > it->second[0]) {
                // cout << "add up : " << (array<int,3>{nx->second[1], it->second[1], id}) << endl;
                res.push_back({nx->second[1], it->second[1], id});
            } else {
                break;
            }
            m.erase(it);
            it = m.upper_bound(y);
        }
        while(it != m.begin()) {
            it--;
            if(it == m.begin()) break;
            auto nx = it;
            nx--;
            if(nx->second[0] > it->second[0]) {
                // cout << "add down : " << (array<int,3>{nx->second[1], it->second[1], id}) << endl;
                res.push_back({nx->second[1], it->second[1], id});
            } else {
                break;
            }
            m.erase(it);
            it = m.upper_bound(y);
        }
        m[y] = {x, id};
    }

    cout << sz(res) << '\n';
    for(auto x : res) {
        for(int i = 0; i < 3; i++) cout << x[i] + 1 << " \n"[i == 2];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}