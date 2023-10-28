#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    map<int,int> m;


    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        m[num]++;
    }
    if(m.size() > 2) {
        cout << "No\n";
        return;
    }
    
    if((abs((*m.begin()).second - (*prev(m.end())).second)) <= 1 || m.size() == 1) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}