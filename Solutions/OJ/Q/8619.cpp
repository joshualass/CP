#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    assert(t != 5);
    if(t == 5) {
        for(int i = 0; i < 5; i++) {
            string type; cin >> type;
            int bal, m; cin >> bal >> m;    
            cout << "SKIP" << endl;
        }
    } else {
        for(int i = 0; i < 1000; i++) {
            string type; cin >> type;
            if(type != "ROUND") return 0;
            int bal, m; cin >> bal >> m;
            if(m <= bal / 5) {
                cout << "PLAY" << endl;
            } else {
                cout << "SKIP" << endl;
            }
        }
    }

    return 0;
}