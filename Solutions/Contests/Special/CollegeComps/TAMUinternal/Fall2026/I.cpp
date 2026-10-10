#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

vector<int> gulp;

bool sixseven(int x) {
    int seven = 0;
    while(x) {
        if(x % 10 == 6) {
            if(seven) return 1;
        }
        seven = x % 10 == 7;
        x /= 10;
    }
    return 0;
}

void solve() {
    
    int x; cin >> x;
    for(int ss : gulp) {
        if(sixseven(x + ss)) {
            cout << ss << '\n';
            return;
        }
    }

    assert(0);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 67; i < 50000; i++) {
        if(sixseven(i)) gulp.push_back(i);
    }

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}