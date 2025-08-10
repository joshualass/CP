#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> mx(n * 2);
    vector<int> id(n * 2, -1);
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(b > mx[a]) {
            mx[a] = b;
            id[a] = i;
        }
    }

    int cmax = 0;
    vector<int> res;
    for(int i = 0; i < n * 2; i++) {
        if(mx[i] > cmax) {
            cmax = mx[i];
            res.push_back(id[i]);
        }
    }
    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) cout << res[i] + 1 << " \n"[i == res.size() - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}