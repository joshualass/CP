#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
The 2025 ICPC Asia East Continent Final Contest (EC-Final 2025)
I. Redundancy Refrain
*/

/*

be careful with how one greedies. I kind of just guessed and assumed it would be obvious. 

What is the logic when we are considering determining the value of a 0. 
First, scan through the array of values and see if we can use one of those before we use a free value. 
When scanning through the array for the fixed values, we should choose the value which occurs earliest in the array and which is possible to reach .
^^^^^ was nontrivial to achieve, but i was able to come up with some edge cases.


edge cases to consider - found many greedy "solutions", but was able to find good counterexmaples. 

9
8 3
0 1 0 2 1 3 0 2
3 3
1 0 2
9 7
0 1 1 0 5 0 4 0 7
6 6
0 0 0 0 0 0
8 7
1 0 0 0 0 0 0 1
4 2
0 1 2 1
7 2
0 1 2 2 1 0 0
8 2
1 0 0 1 2 0 0 0
5 2
0 1 2 0 0 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;    
    }

    auto check = [&](int d) -> vector<int> {
        // cout << "check d : " << d << endl;
        vector<int> f(k, INT_MAX), b(k, INT_MIN);
        for(int i = 0; i < n; i++) {
            if(a[i] != -1) {
                f[a[i]] = min(f[a[i]], i);
                b[a[i]] = max(b[a[i]], i);
            }
        }

        map<int,int> m;
        vector<int> unvis;

        for(int i = 0; i < k; i++) {
            if(f[i] == INT_MAX) {
                unvis.push_back(i);
            } else {
                if(b[i] < d) {
                    m[f[i]] = i;
                }
                if(b[i] - f[i] > d) return {};
            }   
        }

        vector<int> res(n);
        int active = -1;

        // cout << "d : " << d << endl;

        for(int i = 0; i < n; i++) {
            if(i + d < n && a[i+d] != -1 && b[a[i+d]] == i + d) {
                m[f[a[i+d]]] = a[i+d];
            }
            if(a[i] == -1) {
                if(active == -1 || active != -1 && i - f[active] > d) {
                    while(m.size()) {
                        auto it = m.begin();
                        int val = it->second;
                        if(i - f[val] > d) {
                            m.erase(it);
                        } else {
                            break;
                        }
                    }
                    if(m.empty()) {
                        if(unvis.size()) {
                            int val = unvis.back();
                            unvis.pop_back();
                            m[i + d] = val;
                            f[val] = i;
                        } else {
                            return {};
                        }
                    }
                    auto it = m.begin();
                    active = it->second;
                    f[active] = min(f[active], i);
                } 
                res[i] = active;
                // cout << "i : " << i << " active : " << active << endl;
            } else {
                res[i] = a[i];
                if(f[a[i]] == i) active = a[i];
            }
            // cout << "i : " << i << " active : " << active << endl;
        }
        return res;
    };

    int l = 0, r = n - 1;
    while(l != r) {
        int m = (l + r) / 2;
        if(check(m).size()) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    // cout << "l : " << l << endl;

    auto res = check(l);
    for(int i = 0; i < sz(res); i++) cout << res[i] + 1 << " \n"[i == sz(res) - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}