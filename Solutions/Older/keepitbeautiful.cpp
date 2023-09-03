#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<bool> &x) {
    for(bool y : x) {
        cout << y;
    }
    cout << "\n";
}

void solve() {
    int n; cin >> n;
    
    int least; cin >> least;
    int prev = least;
    bool split = false;
    vector<bool> v(n,true);
    for(int i = 1; i < n; i++) {
        int num; cin >> num;
        if(split) {
            if(!(num <= least && num >= prev)) {
                v[i] = false;
            } else {
                prev = num;
            }
        } else {
            if(num < prev) {
                if(num > least) {
                    v[i] = false;
                } else {
                    split = true;
                    prev = num;
                }
            } else {
                prev = num;
            }
        }
    }
    printV(v);
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}