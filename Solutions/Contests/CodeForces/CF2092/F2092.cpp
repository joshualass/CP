#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> early, late, a(n);
    int p = -1;
    char prev = '\0';
    for(int i = 0; i < n; i++) {
        if(prev != s[i]) {
            p++;
            early.push_back(i);
            late.push_back(i);
        }
        prev = s[i];
        late.back() = i;
        a[i] = p;
    }

    // cout << "early : " << early << "\n";
    // cout << "late : " << late << '\n';
    // cout << "a : " << a << '\n';

    //given previous r and beauty, finds next r, if it exists
    auto get_nx_l = [&](int prevr, int b) -> int {
        if(prevr == n - 1) return n;
        int cb = a[prevr + 1];
        if(cb + b - 1 >= early.size()) return n;
        return max(prevr + 1, early[cb + b - 1]);
    };

    //given previous r and beauty, finds the next latest r, if it exists
    auto get_nx_r = [&](int prevr, int b) -> int {
        if(prevr == n - 1) return n;
        int cb = a[prevr + 1];
        if(cb + b - 1 >= late.size()) return n;
        return late[cb + b - 1];
    };

    //at index i, stores k, delta 
    vector<int> pre(n + 1);
    vector<int> prevs(n + 1);
    
    for(int b = 1; b <= n; b++) {
        int l = -1, r = -1;
        int k = 0;
        while(get_nx_l(l, b) != n) {
            k++;
            l = get_nx_l(l, b);
            r = min(n - 1, get_nx_r(r, b));
            if(l <= prevs[k]) {
                pre[prevs[k]]++;
            } else {
                pre[l]++;
            }
            pre[r+1]--;
            prevs[k] = r + 1;
            // cout << "b : " << b << " k : " << k << " l : " << l << " r : " << r << '\n';
        }
    }
    
    vector<int> cnts(n + 1);
    int score = 0;

    for(int i = 0; i < n; i++) {
        score += pre[i];
        cout << score << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n; cin >> n;
    // ld m = 0;
    // for(int i = 1; i <= n; i++) {
    //     m += ((ld) 1) / i;
    // }

    // cout << n * m * log2l(n) << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}