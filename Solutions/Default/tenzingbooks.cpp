#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x) {
    cout << " --- vector --- \n";
    for(int y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void solve() {
    int n, x; cin >> n >> x;
    int magic = 0;
    vector<int> a(n); for(int &x : a) cin >> x;
    vector<int> b(n); for(int &x : b) cin >> x;
    vector<int> c(n); for(int &x : c) cin >> x;
    for(int i = 0; i < n; i++) {
        if((a[i] | x) == x) {
            magic |= a[i];
        } else {
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        if((b[i] | x) == x) {
            magic |= b[i];
        } else {
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        if((c[i] | x) == x) {
            magic |= c[i];
        } else {
            break;
        }
    }
    // cout << magic << " " << x << "\n";
    cout << (magic == x ? "Yes" : "No") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}