#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T>
void printV(const vector<T> &x) {
    cout << "v: ";
    for(auto &y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    if(n == 1) {
        cout << max(0LL,v[0]) << "\n";
        return;
    }
    vector<ll> prefix(n);
    vector<ll> suffix(n);
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            prefix[i] = v[i];
        } else if(i % 2 == 0) {
            prefix[i] = max(prefix[i-1],v[i]);
        } else {
            prefix[i] = max(0LL,prefix[i-1]);
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        if(i == n - 1) {
            suffix[i] = max(0LL,v[i]);
        } else {
            suffix[i] = suffix[i+1] + max(0LL,v[i]);
        }
    }
    ll most = 0;
    for(int i = 0; i < n-1; i++) {
        most = max(most, prefix[i] + suffix[i+1]);

    }
    // cout << "prefix\n";
    // printV(prefix);
    // cout << "suffix\n";
    // printV(suffix);
    cout << most << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}