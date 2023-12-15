#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    
    int sx, sy; cin >> sx >> sy;
    bool toSwap = (sx + sy) & 1;

    set<int> ones;
    set<int> twos;

    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if((x + y) & 1) {
            twos.insert(i + 1);
        } else {
            ones.insert(i + 1);
        }
    }
    if(toSwap) {
        swap(ones,twos);
    }
    if(ones.size() >= twos.size()) {
        cout << "First" << endl;
        int turn = 0;
        while(ones.size() || twos.size()) {
            if(turn % 2 == 0) {
                if(twos.size()) {
                    cout << (*twos.begin()) << endl;
                    twos.erase(*twos.begin());
                } else {
                    cout << (*ones.begin()) << endl;
                    ones.erase(*ones.begin());
                }
            } else {    
                int idx; cin >> idx;
                if(idx == -1) return;
                if(ones.find(idx) != ones.end()) {
                    ones.erase(idx);
                }
                if(twos.find(idx) != twos.end()) {
                    twos.erase(idx);
                }
            }
            turn++;
        }
    } else {
        cout << "Second" << endl;
        int turn = 0;
        while(ones.size() || twos.size()) {
            if(turn % 2 == 0) {
                int idx; cin >> idx;
                if(idx == -1) return;
                if(ones.find(idx) != ones.end()) {
                    ones.erase(idx);
                }
                if(twos.find(idx) != twos.end()) {
                    twos.erase(idx);
                }
            } else {
                if(ones.size()) {
                    cout << (*ones.begin()) << endl;
                    ones.erase(*ones.begin());
                } else {
                    cout << (*twos.begin()) << endl;
                    twos.erase(*twos.begin());
                }
            }
            turn++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}