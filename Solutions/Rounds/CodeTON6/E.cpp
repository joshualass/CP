#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() { //did not read the non-overlapping part :)
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    vector<bool> poss(8193,false);
    poss[0] = true;
    for(int i = 1; i <= n; i++) {
        unordered_set<int> s;
        for(int j = 0; j < n; j++) {
            if(v[j] == i) {
                s.clear();
            } else if(v[j] < i && s.find(v[j]) == s.end()) {
                s.insert(v[j]);
            }
            if(s.size() == i) {
                poss[i] = true;
            }
        }

    }
    int most = 0;
    for(int i = 0; i < poss.size(); i++) {
        for(int j = 0; j < poss.size(); j++) {
            if(poss[i] && poss[j]) {
                poss[i^j] = true;
                most = max(most,i^j);
            }
        }
    }
    cout << most << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}