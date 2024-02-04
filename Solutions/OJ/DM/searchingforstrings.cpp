#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct stringHash {
    const ll MOD = 1e9 + 9, B = 9973;
    vector<ll> hashes;
    vector<ll> pows;
    int n;

    stringHash(string s) {
        this->n = s.size();
        pows.push_back(1);
        for(int i = 0 ; i < n; i++) {
            pows.push_back(pows.back() * B % MOD);
        }    
        hashes.push_back(0);
        for(int i = 0; i < n; i++) {
            hashes.push_back((hashes[i] * B + s[i]) % MOD);
        }
    }

    ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        assert(l >= 0 && r <= n);
        return (hashes[r] - hashes[l] * pows[r-l] % MOD + MOD) % MOD;
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
    
    set<int> found_hashes;
    vector<int> v(26);
    for(int i = 0; i < n.size(); i++) {
        v[n[i] - 'a']++;
    }
    // cout << "v : " << v << '\n';
    vector<int> curr(26);
    for(int i = 0; i < h.size(); i++) {
        curr[h[i] - 'a']++;
        if(i - n.size() >= 0) {
            curr[h[i - n.size()] - 'a']--;
        }
        // cout << "i : " << i << " curr : " << curr << "\n";
        if(v == curr) {
            // cout << "inserting : 
            // cout << "inserting i : " << i << '\n';
            // cout << "l : " << i + 1 - n.size() << " r : " << i + 1 << '\n';
            found_hashes.insert(sh.get_hash(i + 1 - n.size(),i + 1));
        }
    }
    cout << found_hashes.size() << '\n';
    return 0;
}