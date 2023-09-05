#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<ll> &x) {
    cout << " --- vector --- \n";
    for(ll y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int>v(n);
    ll sum = 0;
    for(int &x: v) {
        cin >> x;
        sum+= x;
    }

    sort(v.begin(),v.end());
    vector<ll> prefs(n);
    vector<ll> suffs(n);
    ll tempsum = 0;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            prefs[i/2] = tempsum;
        }
        tempsum += v[i];
    }

    tempsum = 0;
    for(int i = 0; i < n; i++) {
        suffs[i] = tempsum;
        tempsum += v[n-i-1];
    }
    ll least = LLONG_MAX;
    // cout << "least before: " << least << "\n";
    for(int i = 0; i <= k; i++) {
        if(prefs[i] == 0 && i > 0) {
            break;
        }
        // cout << " " << prefs[i] << " " << suffs[k-i];
        // cout << "? " << prefs[i] + suffs[k-i];
        least = min(least, prefs[i] + suffs[k-i]);
    }
    // printV(prefs);
    // printV(suffs);
    // cout << "sum: " << sum << "\n";
    // cout << "least: " << least << "\n";
    cout << sum - least << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}