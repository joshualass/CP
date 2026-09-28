#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;

    vector<int> a;
    for(int i = 0; i < s.size(); i++) if(s[i] == '#') a.push_back(i);

    for(int i = 0; i < a.size(); i += 2) {
        cout << a[i] + 1 << "," << a[i+1] + 1 << '\n';
    }

    return 0;
}
