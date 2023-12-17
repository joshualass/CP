#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    string str; cin >> str;

    vector<int> idxs;
    vector<char> chars;
    int lo = -1;
    for(int i = 25; i >= 0; i--) {
        for(int j = lo + 1; j < n; j++) {
            if(str[j] == (i + 'a')) {
                idxs.push_back(j);
                chars.push_back(str[j]);
                lo = j;
            }
        }
    }
    int maxcnt = 1;
    for(int i = 1; i < idxs.size(); i++) {
        if(str[idxs[i]] != str[idxs[i-1]]) break;
        maxcnt++;
    }
    int ops = idxs.size() - maxcnt;

    vector<char> upd(n);
    for(int i = 0; i < n; i++) {
        upd[i] = str[i];
    }
    sort(chars.begin(), chars.end());
    for(int i = 0; i < idxs.size(); i++) {
        // char c = str[idxs[i]];
        // int upd_idx = idxs[(i + ops) % idxs.size()];
        // upd[upd_idx] = c;
        upd[idxs[i]] = chars[i];
    }
    // cout << "upd : " << upd << '\n';
    bool issorted = is_sorted(upd.begin(), upd.end());
    if(issorted) {
        cout << ops << '\n';
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}