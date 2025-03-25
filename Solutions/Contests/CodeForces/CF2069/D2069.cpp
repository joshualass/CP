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

    string s; cin >> s;

    int len = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != s[s.size()-i-1]) break;
        len++;
    }

    if(len == s.size()) {
        cout << "0\n";
        return;
    }

    s = s.substr(len, s.size() - len * 2);
    int n = s.size();

    vector<vector<int>> p(26, vector<int>(n + 1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 26; j++) {
            p[j][i+1] = p[j][i];
        }
        p[s[i] - 'a'][i + 1]++;
    }

    auto get = [&](int l, int r) -> vector<int> {
        vector<int> res(26);
        for(int i = 0; i < 26; i++) {
            res[i] = p[i][r] - p[i][l];
        }
        return res;
    };

    int same_len = 0;
    while(s[n/2 + same_len] == s[n/2 - same_len-1]) same_len++;

    int res = -1;

    for(int i = 0; i < n; i++) {
        if(i >= n / 2) {
            int ok = 1;
            vector<int> a = get(0, i + 1), b = get(i + 1, n);
            for(int j = 0; j < 26; j++) {
                if(a[j] < b[j]) ok = 0;
            }
            if(ok) {
                res = accumulate(a.begin(), a.end(), 0);
                break;
            }
            ok = 1;
            a = get(0, n - i - 1), b = get(n - i - 1, n);
            for(int j = 0; j < 26; j++) {
                if(a[j] > b[j]) ok = 0;
            }
            if(ok) {
                res = accumulate(b.begin(), b.end(), 0);
                break;
            }
        } else {
            vector<int> a = get(0, i + 1), b = get(n - i - 1, n);
            if(a == b && i + 1 + same_len >= n / 2) {
                res = accumulate(a.begin(), a.end(), 0);
                break;
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}