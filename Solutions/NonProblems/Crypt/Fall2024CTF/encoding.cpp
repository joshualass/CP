#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    set<string> ss;
    for(int i = 0; i < s.size(); i += 4) {
        ss.insert(s.substr(i,4));
    }

    // cout << ss.size() << '\n';

    cout << ss << '\n';

    return 0;
}