#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    vector<int> vis(n), st;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            st.push_back(i);
        } else if(s[i] == '2') {
            if(sz(st)) {
                vis[st.back()] = 1;
                st.pop_back();
            } else {
                vis[i] = 1;
            }
        } else {
            vis[i] = 1;
        }
    }

    cout << count(vis.begin(), vis.end(), 0) << '\n';
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            cout << i + 1 << " ";
        }
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}