#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<pair<array<int,2>, char>> sections;
    int best = 0, cnt = 0;
    char c = '\0';

    for(int i = 0; i < n; i++) {
        if(s[i] != c) {
            if(c != '\0') {
                sections.push_back({{best, cnt}, c});
            }
            best = a[i], cnt = 1;
            c = s[i];
        } else {
            if(a[i] > best) {
                best = a[i];
                cnt = 1;
            } else if(a[i] == best) {
                cnt++;
            }
        }
    }

    if(c != '\0') {
        sections.push_back({{best, cnt}, c});
    }

    if(sections.back().second == '#') sections.pop_back();
    if(sections.begin()->second == '#') sections.erase(sections.begin());

    // cout << "sections : " << sections << endl;

    int mx_all = 0, mx_open = 0;
    for(auto [info, ct] : sections) {
        mx_all = max(mx_all, info[0]);
        if(ct == '.') mx_open = max(mx_open, info[0]);
    }

    ll res = 0;
    for(int i = 2; i < sz(sections); i += 2) {
        int ok;
        if(mx_all == mx_open) {
            ok = sections[i-2].first[0] == mx_all || sections[i-1].first[0] == mx_all || sections[i].first[0] == mx_all;
        } else {
            ok = sections[i-1].first[0] == mx_all;
        }
        if(ok) res += 1LL * sections[i-2].first[1] * sections[i].first[1];
    }
    
    cout << res << '\n';

    return 0;
}
