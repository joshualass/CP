#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    stack<char> st;
    for(char c : s) {
        if(st.empty() || c != st.top()) st.push(c);
        else st.pop();
    }

    cout << (sz(st) ? "NO" : "YES") << "\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}