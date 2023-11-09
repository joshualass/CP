#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    bool poss = true;
    vector<int> ans(n);
    set<int> found;
    bool condone = false;
    int condtwoidx = -1;
    bool condtwo = false;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        ans[i] = 1;
        if(condone && condtwo) {
            continue;
        }
        if(found.find(num) != found.end()) {
            if(!condone) {
                condone = true;
                ans[i] = 2;
                condtwoidx = num;
            } else if(num != condtwoidx) {
                ans[i] = 3;
                condtwo = true;
            }
        }
        found.insert(num);
    }
    if(condone && condtwo) {
        for(auto &x : ans) cout << x << " ";
    } else {
        cout << "-1";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}