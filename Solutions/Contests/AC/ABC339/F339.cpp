#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll mods [5] = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll gh(string num, ll mod) {
    ll val = 0;
    for(int i = 0; i < num.size(); i++) {
        val *= 10;
        val += (num[i] - '0');
        val %= mod;
    }
    return val;
}

vector<ll> get_hash(string num) {
    vector<ll> hashes;
    for(int i = 0; i < 5; i++) {
        hashes.push_back(gh(num,mods[i]));
    }
    return hashes;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    map<vector<ll>,int> freqs;

    vector<vector<ll>> hashes;

    for(int i = 0; i < n; i++) {
        string num; cin >> num;
        vector<ll> hv = get_hash(num);
        freqs[hv]++;
        hashes.push_back(hv);
        // cout << "num : " << num << " hv : " << hv << '\n';
    }

    ll ans = 0;
    vector<ll> res(5);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 5; k++) {
                res[k] = hashes[i][k] * hashes[j][k] % mods[k];
            }
            if(freqs.count(res)) {
                ans += freqs[res];
            }
        }
    }
    cout << ans;
    return 0;
}