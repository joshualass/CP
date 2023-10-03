#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) cout << x.first << " " << x.second << "| ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    ll ans = 0;
    int r = -1;
    unordered_map<int,int> m;
    for(int i = 0; i < n; i++) {
        if(i != 0) {
            m[v[i-1]]--;
            if(m[v[i-1]] == 0) m.erase(v[i-1]);
        }
        while(r + 1 != n && m.size() <= k) {
            if(m.find(v[r+1]) == m.end()) {
                if(m.size() == k) {
                    break;
                } else { 
                    m[v[r+1]] = 1;
                    r++;
                }
            } else {
                m[v[r+1]]++;
                r++;
            }
        }
        // cout << "r: " << r << " i: " << i << "\n";
        // cout << m << "\n";
        ans += r - i + 1;
    }
    cout << ans << "\n";
    return 0;
}