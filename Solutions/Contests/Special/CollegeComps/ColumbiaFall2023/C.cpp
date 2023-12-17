#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string str; cin >> str;
    int ccnt = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == 'c') ccnt++;
    }
    vector<int> ans(0);
    for(int i = 0; i < str.size(); i++) {
        if(i < str.size() - ccnt) {
            if(str[i] == 'c') ans.push_back(i);
        } else {
            if(str[i] != 'c') ans.push_back(i);
        }
    }
    if(ans.size() == 0) {
        cout << "1\n1\n";
    } else {
        cout << ans.size() << "\n";
        for(auto x : ans) cout << ++x << " ";
    }
    

    return 0;
}