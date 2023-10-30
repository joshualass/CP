#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, q; cin >> n >> q;

    vector<int> a(n);
    set<int> s;
    vector<int> b;

    for(auto &x: a) cin >> x;
    
    for(int i = 0; i < q; i++) {
        int num; cin >> num;
        if(s.find(num) == s.end()) {
            b.push_back(num);
            s.insert(num);
        }
    }

    for(int i = 0; i < n; i++) {
        for(auto x : b) {
            if(a[i] % (1 << x) == 0) {
                a[i] += (1 << (x - 1));
            }
        }
    }

    for(auto x : a) cout << x << " ";
    cout << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}