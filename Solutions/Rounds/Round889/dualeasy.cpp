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
    int n; cin >> n;
    int most = -1;
    int idx = -1;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    for(int i = 0; i < n; i++) {
        if(abs(v[i]) > most) {
            most = abs(v[i]);
            idx = i;
        }
    }
    int change = (v[idx] > 0 ? 1 : -1);
    int start = (v[idx] > 0 ? 0 : n-1);
    cout << n * 2 << "\n";
    v[start] = v[idx] * 2;
    cout << start + 1 << " " << idx + 1 << "\n";
    cout << start + 1 << " " << idx + 1 << "\n";
    start += change;
    for(int i = start; i < n && i >= 0; i += change) {
        v[i] = v[i] + v[i - change] * 2;
        cout << i + 1 << " " << i + 1 - change << "\n";
        cout << i + 1 << " " << i + 1 - change << "\n";
    }
    // printV(v);
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
