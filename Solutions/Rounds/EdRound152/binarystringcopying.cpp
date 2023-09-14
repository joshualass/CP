#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
void solve() {
    set<pair<int,int>> s;
    int n, m; cin >> n >> m;
    string bin; cin >> bin;
    set<int> zeros;
    set<int> ones;
    for(int i = 0; i < n; i++) {
        if(bin[i] == '0') {
            zeros.insert(i);
        } else {
            ones.insert(i);
        }
    }
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        --l;
        --r;
        if(ones.lower_bound(l) == ones.end()) {
            // cout << "unchange 1 l: " << l << " r: " << r << "\n";
            s.insert({-1,-1});
            continue;
        }
        int L = *(ones.lower_bound(l));
        if(L > r) {
            // cout << "unchange 2 l: " << l << " r: " << r << "\n";
            s.insert({-1,-1});
            continue;
        }
        if(zeros.upper_bound(r) == zeros.begin()) {
            // cout << "unchange 3 l: " << l << " r: " << r << "\n";
            s.insert({-1,-1});
            continue;
        }
        int R = *(--zeros.upper_bound(r));
        if(R < l) {
            // cout << "unchange 4 l: " << l << " r: " << r << "\n";
            s.insert({-1,-1});
            continue;
        }
        if(R < L) {
            // cout << "unchanged 5 l: " << l << " r: " << r << "\n";
            s.insert({-1,-1});
            continue;
        }
        // cout << "insert: L: " << L << " R: " << R << "\n";
        s.insert({L,R});
    }
    cout << s.size() << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
