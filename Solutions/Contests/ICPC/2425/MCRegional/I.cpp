#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;


template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}


vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c; cin >> r >> c;
    vector<string> a(r);
    for(auto &x : a) cin >> x;

    vector<vector<int>> mr(r,vector<int>(c));
    vector<vector<int>> mc(r,vector<int>(c));

    for(int i = 0; i < r; i++) {
        string s = a[i];
        vector<int> m = manacher(s);
        // cout << "s : " << s << '\n';?
        // cout << "m : " << m << '\n';

        for(int j = 0; j < s.size() * 2 - 1; j++) {
            for(int k = 0; k < m[j] / 2; k++) {
                mr[i][j / 2 - k] = max(mr[i][j / 2 - k], m[j] - 1);
                mr[i][j / 2 + k + (m[j] & 1)] = max(mr[i][j / 2 + k + (m[j] & 1)], m[j] - 1);
            }
        }

        // cout << "mr[i] : " << mr[i] << '\n';

    }

    for(int i = 0; i < c; i++) {
        string s = "";
        for(int j = 0; j < r; j++) {
            s.push_back(a[j][i]);
        }   
        vector<int> m = manacher(s);
        for(int j = 0; j < s.size() * 2 - 1; j++) {
            for(int k = 0; k < m[j] / 2; k++) {
                mc[j / 2 - k][i] = max(mc[j / 2 - k][i], m[j] - 1);
                mc[j / 2 + k + (m[j] & 1)][i] = max(mc[j / 2 + k + (m[j] & 1)][i], m[j] - 1);
            }
        }
    }

    int res = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            res = max(res,mr[i][j] * mc[i][j]);
        }
    }

    cout << res << '\n';

    return 0;
}