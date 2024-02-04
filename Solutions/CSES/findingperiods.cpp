#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct stringhash {
    const ll M1 = 998244353, B1 = 9973;
    const ll M2 = 1e9 + 9, B2 = 9931;
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    int n;

    stringhash(string s) {
        this->n = s.size();
        p1.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p1.push_back(p1.back() * B1 % M1);
        }
        p2.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p2.push_back(p2.back() * B2 % M2);
        }
        h1.push_back(0);
        for(int i = 0; i < n; i++) {
            h1.push_back((h1[i] * B1 + s[i]) % M1);
        }
        h2.push_back(0);
        for(int i = 0; i < n; i++) {
            h2.push_back((h2[i] * B2 + s[i]) % M2);
        }
    }

    pair<ll,ll> get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        assert(l >= 0 && r <= n);
        return {
            (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1,
            (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2        
        };
    }

};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    stringhash sh(s);
    int n = s.size();
    vector<bool> poss(n + 1);
    for(int length = n; length >= 1; length--) {
        if(length * 2 <= n) {
            if(poss[length * 2]) {
                if(sh.get_hash(0,length) == sh.get_hash(length, length * 2)) {
                    poss[length] = 1;
                }
            }
        } else {
            if(sh.get_hash(0,n - length) == sh.get_hash(length, n)) {
                poss[length] = 1;
            }
        }
    }

    for(int i = 0; i <= n; i++) {
        if(poss[i]) {
            cout << i << ' ';
        }
    }

    return 0;
}