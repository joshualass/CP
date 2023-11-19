#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    pair<int,int> best = {-1,-1};
    vector<int> v(n);

    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        v[--num]++;
        if(v[num] > best.first || v[num] == best.first && num < best.second) {
            best = {v[num], num};
        }
        cout << best.second + 1 << '\n';
    }

    return 0;
}