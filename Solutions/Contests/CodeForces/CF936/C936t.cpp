#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto op = [](vector<array<int,2>> a, int x) -> vector<array<int,2>> {
        int n = a.size();
        vector<array<int,2>> res;
        for(int i = 0; i < x; i++) {
            res.push_back(a[n-i-1]);
            res.back()[1] ^= 1;
        }
        for(int i = x; i < n; i++) {
            res.push_back(a[i-x]);
        }
        return res;
    };

    map<vector<array<int,2>>,int> m;

    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        a[i][0] = i;
    }

    queue<pair<vector<array<int,2>>,int>> q;
    q.push({a,0});
    m[a] = 0;
    while(q.size()) {
        auto [b,s] = q.front();
        q.pop();
        // swap any 2 characters 6 operations
        if(b[0][0] == 0 && b[1][0] == 3 && b[2][0] == 2 && b[3][0] == 1 && b[4][0] == 4 && b[0][1] == 0 && b[2][1] == 0 && b[4][1] == 0) { 
            cout << "b : " << b << " s : " << s << '\n';
        }    
        for(int x = 0; x <= n; x++) {
            if(m.count(op(b,x))) continue;
            q.push({op(b,x), s + 1});
            m[op(b,x)] = s+1;
        }
    }

    return 0;
}