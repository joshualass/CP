#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    int best = INT_MAX;
    vector<int> smallest(n);
    for(int i = 0; i < v.size(); i++) {
        smallest[i] = (((v[i] - 1) % k) + 1);
    }
    // for(auto x : smallest) cout << x << ' ';
    // cout << "\n";
    if(k != 4) {
        if(k != 4) {
            cout << k - *max_element(smallest.begin(),smallest.end()) << '\n';
        } else {
            best = k - *max_element(smallest.begin(),smallest.end());
        }
    } else {
        int twos = 0;
        int fours = 0;
        bool close = false;
        for(int i = 0; i < v.size(); i++) {
            if(v[i] % 2 == 0) {
                twos++;
            }
            if(v[i] % 4 == 0) {
                fours++;
            }
            if(v[i] % 4 == 3) close = true;
        }
        if(fours || twos >= 2) {
            cout << "0\n";
        } else {
            if(twos && n >= 2 || close) {
                cout << "1\n";
            } else if(n >= 2) {
                cout << "2\n";
            } else {
                cout << k - *max_element(smallest.begin(),smallest.end()) << '\n';
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}