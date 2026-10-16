#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

int hidden_x;

int debug = 0;
// int debug = 1;

const int M = 3334;

int solve() {

    int asks = 0;
    int aura = 0;
    
    auto ask = [&](int a, int b) -> int {
        asks++;
        assert(-inf <= a && a <= inf && -inf <= b && b <= inf);
        if(debug) {
            int res = min(abs(a - hidden_x), abs(b - hidden_x)); 
            aura += res;
            return res;
        } else {
            cout << a << " " << b << endl;
            int res; cin >> res;
            return res;
        }
    };

    const int N = 10000;
    int p = (N + 6) / 7;
    int a = p, b = p * 5;
    int d1 = ask(a, b);
    if(d1 <= p) {
        int d2 = ask(a - 1, b + 1);
        if(d2 < d1) {
            a = a - d1;
            b = b + d1;
        } else {
            a = a + d1;
            b = b - d1;
        }
    } else {
        int q = p * 3 - 2;
        int d2 = ask(q, b + d1);
        if(d2) {
            a = q - d2;
            b = q + d2;
        } else {
            a = q;
            b = b + d1;
        }
    }

    while(asks < 10) ask(a, b);
    // cout << "hidden x : " << hidden_x << " aura : " << aura << endl;
    return aura;
}

map<set<int>, array<int,3>> m;

int dfs(set<int> s) {
    if(m.count(s) == 0) {
        if(sz(s) == 1) {
            m[s] = {0, -1, -1};
        } else {
            // cout << "solving set s : " << s << endl;
            int lo = (*s.begin()) - 1;
            int hi = (*--s.end()) + 1;
            array<int,3> res = {INT_MAX, INT_MAX, INT_MAX};
            for(int a = lo; a <= hi; a++) {
                for(int b = a; b <= hi; b++) {
                    map<int,set<int>> t;
                    int wc = 0;
                    for(int x : s) {
                        int dis = min(abs(x - a), abs(x - b));
                        t[dis].insert(x);
                    }
                    // cout << "a : " << a << " b : " << b << " wc : " << wc << endl;
                    for(auto [dis, ss] : t) {
                        // cout << "dis : " << dis << " ss : " << ss << endl;
                        if(ss != s) {
                            wc = max(wc, dis + dfs(ss));
                        } else {
                            wc = INT_MAX;
                        }
                    }

                    res = min(res, {wc, a, b});
                }
            }
            // cout << "res : " << res << endl;
            m[s] = res;
        }
    }
    return m[s][0];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // array<ll,2> best = {inf, inf};

    // for(int d = 1; d <= 5000; d++) {

    //     ll worst_case = max()

    // }

    
    if(debug == 0) {
        int casi; cin >> casi;
        for(int i = 0; i < casi; i++) {
            
            solve();
        }
    } else {
        // vector<int> a(100);
        // iota(a.begin(), a.end(), 1);
        // set<int> s(a.begin(), a.end());
        // dfs(s);
    
        // cout << m[s] << endl;
        // cout << m[{1,5,6,10}] << endl;

        for(int i = 1; i <= 10000; i++) {
            hidden_x = i;
            // cout << "i : " << i << endl;
            assert(solve() <= M);
        }
    }

    return 0;
}
