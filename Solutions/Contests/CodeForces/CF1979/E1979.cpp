#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

std::ostream& operator<<(std::ostream& os, const array<int,3> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}



array<int,3> solve1(vector<array<int,2>> &a, int d) {

    unordered_map<int, vector<array<int,3>>> m1;
    unordered_map<int, vector<array<int,3>>> m2;

    for(int i = 0; i < a.size(); i++) {
        m1[a[i][1] - a[i][0]].push_back({a[i][0], a[i][1], i});
        m2[a[i][0] + a[i][1]].push_back({a[i][0], a[i][1], i});
    }

    for(auto &[u,v] :m1) sort(v.begin(), v.end());
    for(auto &[u,v] : m2) sort(v.begin(), v.end());

    d /= 2;
    for(int i = 0; i < a.size(); i++) {
        int x = a[i][0], y = a[i][1];
        int m1id = y - x + d * 2;
        int m2id = x + y + d * 2;
        vector<array<int,3>> &v1 = m1[m1id];
        vector<array<int,3>> &v2 = m2[m2id];
        // cout << "x : " << x << " y : " << y << '\n';
        // cout << "s1 : " << s1 << '\n';
        // cout << "s2 : " << s2 << '\n';
        vector<array<int,3>>::iterator it1 = lower_bound(v1.begin(), v1.end(), array<int,3>{x-d,-MOD,-MOD});
        vector<array<int,3>>::iterator it2 = upper_bound(v2.begin(), v2.end(), array<int,3>{x+d,MOD,MOD});
        if(it1 != v1.end() && it2 != v2.begin()) {
            array<int,3> p1 = *it1;
            array<int,3> p2 = *--it2;
            if(abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]) == d * 2 && abs(a[i][0] - p1[0]) + abs(a[i][1] - p1[1]) == d * 2 && abs(a[i][0] - p2[0]) + abs(a[i][1] - p2[1]) == d * 2) {
                // cout << "ret\n";
                return {i, p1[2], p2[2]};
            }
        }
    }

    return {-1,-1,-1};
}

void rotateCC(vector<array<int,2>> &a) {
    for(array<int,2> &x : a) {
        swap(x[0],x[1]);
        x[0] *= -1;
    }
}

void solve() {
    
    int n, d; cin >> n >> d;
    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    array<int,3> res = {-1,-1,-1};
    for(int i = 0; i < 4; i++) {
        res = max(res,solve1(a,d));
        rotateCC(a);
    }

    cout << res[0] + 1 << " " << res[1] + 1 << " " << res[2] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}