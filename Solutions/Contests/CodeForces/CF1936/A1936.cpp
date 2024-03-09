#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

char ask(int a, int b, int c, int d) {
    cout << "? " << a << " " << b << " " << c << " " << d << endl;
    char ans; cin >> ans;
    return ans;
}

void solve() {
    int n; cin >> n;
    int mi = 0;
    for(int i = 1; i < n; i++) {
        char c = ask(mi,mi,i,i);
        if(c == '<') {
            mi = i;
        }
    }
    vector<int> maxes(1,0);
    for(int i = 1; i < n; i++) {
        char c = ask(maxes.back(),mi,i,mi);
        if(c == '<') {
            maxes.clear();
            maxes.push_back(i);
        } else if(c == '=') {
            maxes.push_back(i);
        }
    }
    int mini = 0;
    for(int i = 1; i < maxes.size(); i++) {
        char c = ask(maxes[mini],maxes[mini],maxes[i],maxes[i]);
        if(c == '>') {
            mini = i;
        }
    }
    cout << "! " << mi << " " << maxes[mini] << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}