#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct stringHash {
    const ll M1 = 998244353, B1 = 9973;
    const ll M2 = 1e9 + 9, B2 = 9931;
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    int n;

    stringHash(string s) {
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string n, h; cin >> n >> h;
    stringHash sh(h);
    
    set<pair<ll,ll>> found_h1;
    vector<int> v(26);
    for(int i = 0; i < n.size(); i++) {
        v[n[i] - 'a']++;
    }
    // cout << "v : " << v << '\n';
    vector<int> curr(26);
    for(int i = 0; i < h.size(); i++) {
        curr[h[i] - 'a']++;
        if(i - (int) n.size() >= 0) {
            curr[h[i - (int) n.size()] - 'a']--;
        }
        // cout << "i : " << i << " curr : " << curr << "\n";
        if(v == curr) {
            // cout << "inserting : 
            // cout << "inserting i : " << i << '\n';
            // cout << "l : " << i + 1 - n.size() << " r : " << i + 1 << '\n';
            found_h1.insert(sh.get_hash(i + 1 - (int) n.size(),i + 1));
        }
    }
    cout << found_h1.size() << '\n';
    return 0;
}