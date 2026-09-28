#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool ismatch(string &s, string &t, int idx) {
    if(idx < 0 || idx + t.size() > s.size()) return false;
    for(int i = 0; i < t.size(); i++) {
        if(s[i + idx] != '#' && s[i + idx] != t[i]) return false;
    }
    return true;
}

void passforward(string &s, string &t) {
    for(int i = 0; i < s.size(); i++) {
        if(ismatch(s,t,i)) {
            for(int j = 0; j < t.size(); j++) {
                s[i+j] = '#';
            }
        }
    }
}

void passbackward(string &s, string &t) {
    for(int i = s.size()-1; i >= 0; i--) {
        if(ismatch(s,t,i)) {
            for(int j = 0; j < t.size(); j++) {
                s[i+j] = '#';
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    string s,t; cin >> s >> t;

    for(int i = 0; i < 10; i++) {
        passforward(s,t);
        passbackward(s,t);
    }

    for(int i = 0 ; i < n; i++) {
        if(s[i] != '#') {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
    

    return 0;
}