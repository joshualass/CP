// https://codeforces.com/contest/1810/problem/B
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    if(n & 1) {
        n -= 1;
        bool start = false;
        vector<int> ans;
        for(int i = 30; i >= 0; i--) {
            if((n >> i) & 1) {
                // cout << "2 ";a
                ans.push_back(2);
                start = true;
            } else if(start) {
                // cout << "1 ";
                ans.push_back(1);
            }
        }
        ans.pop_back();
        cout << ans.size() << '\n';
        for(auto x : ans) cout << x << ' ';
        cout << '\n';
    } else {
        cout << "-1\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}