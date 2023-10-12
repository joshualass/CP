#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    // int n, k; cin >> n >> k;
    // unordered_set<int> s;
    // for(int i = 0; i < n; i++) {
    //     int num; cin >> num;
    // s.insert(num);
    // }
    // cout << (s.find(k) == s.end() ? "NO" : "YES") << "\n";
    int n, k; cin >> n >> k;
    bool found = false;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num == k) found = true;
    }
    cout << (found ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}