#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        s.insert(num);
    }
    s.erase(--s.end());
    cout << *--s.end() << '\n';

    return 0;
}