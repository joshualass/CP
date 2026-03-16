#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
// #define sz(x) (int) (x).size()
 
/*
we have a very greedy snake :)
 
The greedy snake is no longer happy here :( ft
1
1
DDDRULLLDRUUULDRRRUL
 
=> back to dp
*/
 
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
 
template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}
 
template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}
 
template<typename T>
ostream& operator<<(ostream& os, const deque<T>& d) {
    for (auto x : d) os << x << " ";
    return os;
}
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
struct Tree {
	typedef int T;
	static constexpr T unit = -1e9;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
 
// void solve() {
    
//     int n; cin >> n;
//     string s; cin >> s;
//     n = sz(s);
//     vector<int> maxlen(n + 1);
//     int cur = 1, cx = 0, cy = 0;
//     maxlen[0] = cur;
//     map<array<int,2>,int> m;
//     m[{cx,cy}] = -1;
 
//     for(int i = 0; i < n; i++) {
//         int nx = cx, ny = cy;
//         if(s[i] == 'D') {
//             nx++;
//         } else if(s[i] == 'U') {
//             nx--;
//         } else if(s[i] == 'R') {
//             ny++;
//         } else if(s[i] == 'L') {
//             ny--;
//         } else {
//             assert(0);
//         }
//         cur++;
//         if(m.count({nx, ny})) {
//             cur = min(cur, i - m[{nx,ny}]);
//         }
//         cx = nx, cy = ny;
//         m[{nx,ny}] = i;
//         maxlen[i+1] = cur;
//     }
 
//     for(int i = n - 1; i >= 0; i--) {
//         maxlen[i] = min(maxlen[i], maxlen[i+1]);
//     }
 
//     cout << "ml : " << maxlen << endl;
 
//     //
//     map<array<int,2>, int> pos_cnts;
//     set<array<int,2>> bad;
//     deque<array<int,2>> q;
    
//     q.push_back({0,0});
//     pos_cnts[{0,0}]++;
 
//     int res = 1, len = 1;
//     cx = 0, cy = 0;
 
//     for(int i = 0; i < n; i++) {
//         int nx = cx, ny = cy;
//         if(s[i] == 'D') {
//             nx++;
//         } else if(s[i] == 'U') {
//             nx--;
//         } else if(s[i] == 'R') {
//             ny++;
//         } else if(s[i] == 'L') {
//             ny--;
//         } else {
//             assert(0);
//         }
//         //can we eat an apple here?
//         // cout << "i : " << i << endl;
//         // cout << "cx : " << cx << " cy : " << cy << endl;
//         // cout << "nx : " << nx << " ny : " << ny << endl;
//         // cout << "pc : " << pos_cnts << endl;
//         // cout << "bad : " << bad << endl;
//         // cout << "q before : " << q << endl;
//         if(pos_cnts.count({nx, ny}) == 0 && bad.count({nx, ny}) == 0 && maxlen[i + 1] >= len + 1) {
//             len++;
//             bad.clear();
//             // cout << "EAT" << endl;
//         } else {
//             bad.insert(q.front());
//             pos_cnts[q.front()]--;
//             if(pos_cnts[q.front()] == 0) pos_cnts.erase(q.front());
//             q.pop_front();
//             // cout << "SKIP" << endl;
//         }
        
//         q.push_back({nx, ny});
//         pos_cnts[{nx,ny}]++;
 
//         res += len;
//         cx = nx, cy = ny;
//         cout << "i : " << i << " len : " << len << endl;
//     }
 
//     cout << res << '\n';
 
//     // vector<ll> dp(n + 2, -1e18), ndp(n + 2);
//     // dp[1] = 1;
//     // // cout << "i : " << -1 << " dp : " << dp << endl;
//     // for(int i = 0; i < n; i++) {
//     //     ndp.assign(n + 2, -1e18);
//     //     for(int j = 1; j <= n + 1; j++) {
//     //         if(maxlen[i+1] >= j) {
//     //             ndp[j] = max(ndp[j], dp[j] + j);
//     //         }
//     //         if(j + 1 < n + 2 && maxlen[i+1] >= j + 1) {
//     //             // cout << "trigger i : " << i << " j : " << j << " val : " << dp[j] + j + 1 << endl;
//     //             // cout << "j + 1 : " << j + 1 << endl;
//     //             ndp[j+1] = max(ndp[j+1], dp[j] + j + 1);
//     //         }
//     //     }
//     //     swap(dp, ndp);
//     //     cout << "i : " << i << " dp : " << dp << endl;
//     // }
 
//     // cout << *max_element(dp.begin(), dp.end()) << '\n';
 
// }
 
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    n = sz(s);
 
    //compute a, maxlen
    vector<array<int,2>> a(n + 1);
    vector<int> maxlen(n + 1, 1);
    {
        map<array<int,2>,int> m;
        m[a[0]] = 0;
        for(int i = 1; i <= n; i++) {
            a[i] = a[i - 1];
            if(s[i - 1] == 'D') {
                a[i][0]++;
            } else if(s[i - 1] == 'U') {
                a[i][0]--;
            } else if(s[i - 1] == 'R') {
                a[i][1]++;
            } else if(s[i - 1] == 'L') {
                a[i][1]--;
            }
            maxlen[i] = maxlen[i - 1] + 1;
            if(m.count(a[i])) {
                maxlen[i] = min(maxlen[i], i - m[a[i]]);
            }
            m[a[i]] = i;
        }
        for(int i = n - 1; i >= 0; i--) {
            maxlen[i] = min(maxlen[i], maxlen[i+1]);
        }
    }
 
    // cout << "a : " << a << endl;
    // cout << "maxlen : " << maxlen << endl;
 
    //compute pc
    vector<vector<int>> pc(n + 1, vector<int>(n + 1));
    {
        map<array<int,2>, int> m;
        m[a[0]] = 0;
        for(int i = 1; i <= n; i++) {
            int val = (m.count(a[i]) ? m[a[i]] : -1);
            for(int j = 1; j <= n; j++) {
                if(val != -1) {
                    pc[i][j] = max(pc[i][j], val + j);
                }
            }
            m[a[i]] = i;
        }
    }
 
    // cout << "PC" << endl;
    // for(int i = 0; i <= n; i++) cout << "i : " << i << " pc[i] : " << pc[i] << endl;
 
    //compute dp
    // vector<vector<int>> dp(n + 1, vector<int>(n + 2, -1e9));
    // dp[0][1] = 0;
    vector<Tree> dp(n + 2, Tree(n + 1));
    dp[1].update(0, 0);
    int res = n + 1;
    {
        for(int len = 2; len <= n + 1; len++) {
            for(int i = 1; i <= n; i++) {
                if(maxlen[i] >= len && len > 1 && pc[i][len-1] < i) {
                    // int best = -1e9;
                    // for(int j = pc[i][len-1]; j < i; j++) {
                    //     best = max(best, dp[j][len - 1] + (len - 1) * (i + 1) - (i + 1) * len + 1);
                    // }
                    // cout << "i : " << i << " len : " << len << " best : " << best << endl;
                    // dp[i][len] = max(dp[i][len], best);
                    dp[len].update(i, dp[len - 1].query(pc[i][len-1], i) + (len - 1) * (i + 1) - (i + 1) * len + 1);
                }
                // res = max(res, dp[i][len] + (n + 1) * len);
                res = max(res, dp[len].query(i, i + 1) + (n + 1) * len);
            }
        }
    }
 
    // cout << "DP" << endl;
    // for(int i = 0; i <= n; i++) cout << "i : " << i << " dp[i] : " << dp[i] << endl;
 
    cout << res << '\n';
 
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int casi; cin >> casi;
    while(casi-->0) solve();
 
    return 0;
}