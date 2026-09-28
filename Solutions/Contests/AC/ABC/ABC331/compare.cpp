#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("test.out","r",stdin);
    
    
    vector<string> mine;

    string str;
    for(int i = 0; i < 50252; i++) {
        cin >> str;
        mine.push_back(str);
    }
    cout << "alive1\n";
    // freopen("smallout.txt","r",stdin);
    vector<string> ans;
    while(cin >> str) {
        ans.push_back(str);
    }
    cout << mine.size() << " " << ans.size() << "\n";
    int cnt = 0;
    for(int i = 0; i < mine.size(); i++) {
        if(mine[i] != ans[i]) {
            cout << "mine : " << mine[i] << " ans : " << ans[i] << " i : " << i << '\n';
        } else {
            cnt++;
        }
    }
    cout << cnt << '\n';
    return 0;
}