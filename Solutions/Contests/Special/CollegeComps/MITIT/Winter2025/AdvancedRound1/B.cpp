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
    vector<int> l,d,el,ed;
    for(int i = 0; i < n; i++) {
        int p, s; cin >> p >> s;
        if(s) {
            l.push_back(p);
        } else {
            d.push_back(p);
        }
    }
    for(int i = 0; i < n; i++) {
        int q, s; cin >> q >> s;
        if(s) {
            el.push_back(q);
        } else {
            ed.push_back(q);
        }
    }

    sort(l.begin(),l.end());
    sort(d.begin(),d.end());
    sort(el.begin(),el.end());
    sort(ed.begin(),ed.end());

    // cout << "l : " << l << '\n';
    // cout << "d : " << d << '\n';
    // cout << "el : " << el << '\n';
    // cout << "ed : " << ed << '\n';

    multiset<int> ms;
    for(int i = ((int) el.size()) - 1; i >= 0; i--) {
        while(l.size() && l.back() * 2 >= el[i]) {
            ms.insert(l.back());
            l.pop_back();
        }
        while(d.size() && d.back() >= el[i]) {
            ms.insert(d.back() * 2);
            d.pop_back();
        }
        if(ms.empty()) {
            cout << "NO\n";
            return;
        }
        ms.erase(ms.begin());
    }
    while(l.size()) {
        ms.insert(l.back());
        l.pop_back();
    }
    while(d.size()) {
        ms.insert(d.back() * 2);
        d.pop_back();
    }

    vector<int> a(ms.begin(), ms.end());
    // cout << "a : " << a << '\n';
    for(int i = 0; i < ed.size(); i++) {
        if(a[i] < ed[i]) {
            cout << "NO\n";
            return;
        }
    }
 
    cout << "YES\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}