#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int n = 100;
vector<int> a[10];
int nim[n + 1];

int get(int x) {
    for(int i = 9; i >= 0; i--) {
        for(int y : a[i]) {
            if(x >= y && (x - y) % 34 == 0) {
                return i;
            }
        }
    }
    assert(0);
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << "\n";
    return os;
}

// map<vector<int>, int> m;

// int solve_slow(vector<int> stones) {
//     sort(stones.begin(), stones.end());
//     if(m.count(stones) == 0) {
//         int f = 0;
//         for(int i = 0; i < sz(stones); i++) {
//             for(int l = 0; l + 2 <= stones[i]; l++) {
//                 auto c = stones;
//                 c.erase(c.begin() + i);
//                 c.push_back(l);
//                 c.push_back(stones[i] - l - 2);
//                 if(solve_slow(c) == 0) f = 1;
//             }
//         }
//         m[stones] = f;
//     }
//     return m[stones];
// }

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int rc = count(s.begin(), s.end(), 'R');
    int bc = count(s.begin(), s.end(), 'B');
    if(rc > bc) {
        cout << "Alice\n";
        return;
    }
    if(bc > rc) {
        cout << "Bob\n";
        return;
    }
    vector<pair<char,int>> a;
    for(char c : s) {
        if(a.empty() || c != a.back().first) {
            a.push_back({c, 0});
        }
        a.back().second++;
    }

    if(sz(a) == 1) {
        cout << "Bob\n";
        return;
    }

    int nimber = 0;
    int prev = 0;
    for(int i = 1; i < sz(a); i++) {
        auto [c, len] = a[i];
        if(i + 1 == sz(a) || len != 1) {
            int l = i - prev + 1;
            nimber ^= get(l);
            prev = i;
        }
    }

    cout << (nimber ? "Alice" : "Bob") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int x = 16;
    // map<int,set<int>> bad;

    // for(int i = 1; i <= 16; i++) {
    //     for(int j = i; j <= 16; j++) {
    //         if(solve_slow({i, j}) == 0) {
    //             // cout << i << " " << j << endl;
    //             bad[i].insert(j);
    //         }
    //     }
    //     // if(solve_slow({x, i}) == 0) {
    //     //     cout << i << endl;
    //     // }
    // }

    // for(int i = 1; i <= 14; i++) {
    //     for(int j = 14; j <= 14; j++) {
    //         for(int k = 16; k <= 16; k++) {
    //             if(solve_slow({i, j, k}) == 0 && bad[i].count(j) == 0 && bad[i].count(k) == 0 && bad[j].count(k) == 0) {
    //                 cout << i << " " << j << " " << k << endl;
    //             }
    //         }
    //         // if(solve_slow({i, j}) == 0) {
    //         //     cout << i << " " << j << endl;
    //         // }
    //     }
    //     // if(solve_slow({x, i}) == 0) {
    //     //     cout << i << endl;
    //     // }
    // }

    int n = 100;

    for(int i = 0; i <= n; i++) {
        set<int> vis;
        for(int j = 0; j + 2 <= i; j++) {
            int l = j, r = i - j - 2;
            vis.insert(nim[l] ^ nim[r]);
        }
        while(vis.count(nim[i])) nim[i]++;
        a[nim[i]].push_back(i);
    }

    // cout << nim << endl;

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}