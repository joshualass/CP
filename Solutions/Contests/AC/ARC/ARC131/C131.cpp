#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int yoyo = 0;

    set<int> s;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        s.insert(num);
        yoyo ^= num;
    }

    if(n & 1 || s.find(yoyo) != s.end()) {
        cout << "Win\n";
    } else {
        cout << "Lose\n";
    }

    return 0;
}