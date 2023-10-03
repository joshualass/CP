//https://codeforces.com/contest/863/problem/B
//boring
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n*2);
    for(auto &x: v) cin >> x;
    sort(v.begin(),v.end());   
    int best = INT_MAX;
    for(int i = 0; i < n * 2; i++) {
        for(int j = i + 1; j < n * 2; j++) {
            int total = 0;
            int prev = -1;
            for(int k = 0; k < n * 2; k++) {
                if(k == i || k == j) continue;
                if(prev == -1) {
                    prev = v[k];
                } else {
                    total += abs(v[k] - prev);
                    prev = -1;
                }
            }
            best = min(total, best);
        }
    }
    cout << best << "\n";

    return 0;
}