#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    set<int> inter;

    int cnt; cin >> cnt;

    char trash; cin >> trash;

    for(int i = 0; i < cnt; i++) {
        int num; cin >> num;
        inter.insert(num);
    }

    for(int i = 0; i < n - 1; i++) {
        int c; cin >> c;
        set<int> unionss;
        cin >> trash;
        for(int j = 0; j < c; j++) {
            int num; cin >> num;
            if(inter.find(num) != inter.end()) {
                unionss.insert(num);
            }
        }
        inter = unionss;
    }

    cout << (inter.size() ? "YES" : "NO") << '\n';

    return 0;
}