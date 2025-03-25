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
    int a, b, ab, ba; cin >> a >> b >> ab >> ba;

    vector<int> abc, bac;
    int c = 0, p = 0;
    int l = 0; //rhs of previous double

    s.push_back(s.back());

    if(s.back() == 'A') {
        a++;
    } else {
        b++;
    }

    // cout << "s : " << s << '\n';

    for(int i = 1; i < s.size(); i++) {
        if(s[i] == s[i-1]) {
            if(l + 1 != i) {
                char p = s[l], n = s[i];
                if(p == 'A' && n == 'B') {
                    abc.push_back((i - l) / 2);
                } else if(p == 'B' && n == 'A') {
                    bac.push_back((i - l) / 2);
                } else {
                    c += (i - l - 1) / 2;
                }
                l = i;
            }
        }
    }

    sort(abc.rbegin(), abc.rend());
    sort(bac.rbegin(), bac.rend());

    // cout << "abc : " << abc << '\n';
    // cout << "bac : " << bac << '\n';
    // cout << "c : " << c << '\n';

    while(ab && abc.size()) {
        int rem = min(ab, abc.back());
        p += rem;
        ab -= rem;
        abc[abc.size() - 1] -= rem;
        if(abc.back() == 0) abc.pop_back();
    }

    while(ba && bac.size()) {
        int rem = min(ba, bac.back());
        p += rem;
        ba -= rem;
        bac[bac.size() - 1] -= rem;
        if(bac.back() == 0) bac.pop_back();
    }

    int remab = min(ab, c);
    p += remab;
    c -= remab;
    ab -= remab;

    int remba = min(ba, c);
    p += remba;
    c -= remba;
    ba -= remba;

    while(ab && bac.size()) {
        int rem = min(ab, bac.back() - 1);
        p += rem;
        ab -= rem;
        bac.pop_back();
    }

    while(ba && abc.size()) {
        int rem = min(ba, abc.back() - 1);
        p += rem;
        ba -= rem;
        abc.pop_back();
    }

    int ac = count(s.begin(), s.end(), 'A');
    int bc = count(s.begin(), s.end(), 'B');

    cout << (ac <= p + a && bc <= p + b ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}