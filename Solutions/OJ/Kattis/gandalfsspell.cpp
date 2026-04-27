#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;

    vector<string> a;
    cin.ignore();
    while(!cin.eof()) {
        string s; 
        if(!(cin >> s)) break;
        // cout << "s : " << s << endl;
        cin.ignore();
        a.push_back(s);
    }

    // cout << "a : " << a << endl;

    int ok = 1;
    if(sz(s) != sz(a)) ok = 0;

    // cout << "size ok : " << ok << endl;

    map<string, char> m;
    set<char> sc;

    for(int i = 0; ok && i < sz(s); i++) {
        if(m.count(a[i])) {
            if(m[a[i]] != s[i]) ok = 0;
        } else {
            if(sc.count(s[i])) ok = 0;
            m[a[i]] = s[i];
            sc.insert(s[i]);
        }
    }

    cout << (ok ? "True" : "False") << '\n';

    return 0;
}
