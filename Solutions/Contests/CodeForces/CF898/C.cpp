#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    vector<string> target(10);
    for(int i = 0; i < 10; i++) {
        cin >> target[i];
    }
    int pts = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(target[i][j] == 'X') {
                pts += 5 - max(max(abs(5-i),abs(4-i)),max(abs(5-j),abs(4-j)))+1;
            }
        }
    }
    cout << pts << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}