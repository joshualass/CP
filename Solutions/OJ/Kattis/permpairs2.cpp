#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b; cin >> a >> b;
    set<string> visa;
    
    for(int i = 0; i < sz(a); i++) {
        for(int l = 1; i + l <= sz(a); l++) {
            string t = a.substr(i, l);
            sort(t.begin(), t.end());
            visa.insert(t);
        }
    }

    auto get = [&](string s) -> ll {
        map<char,int> m;
        for(char c : s) m[c]++;
        int p = 1;
        ll res = 1;
        for(auto [k, v] : m) {
            for(int i = 1; i <= v; i++) {
                res *= p++;
                res /= i;
            }
        }
        return res;
    };

    ll res = 0;


    for(int i = 0; i < sz(b); i++) {
        for(int l = 1; i + l <= sz(b); l++) {
            string t = b.substr(i, l);
            sort(t.begin(), t.end());
            if(visa.count(t)) {
                visa.erase(t);
                res += get(t);
            }
        }
    }

    cout << res << '\n';

    return 0;
}

/*
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b; cin >> a >> b;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll res = 1;
    if(a != b) res = 0;
    map<char,int> m;
    for(char c : a) m[c]++;
    int p = 1;
    for(auto [k, v] : m) {
        for(int i = 1; i <= v; i++) {
            res *= p++;
            res /= i;
        }
    }

    cout << res << '\n';

    return 0;
}

*/