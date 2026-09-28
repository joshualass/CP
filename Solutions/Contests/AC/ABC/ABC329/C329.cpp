#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // int n; cin >> n;
    // string str; cin >> str;
    // set<string> s;

    // string curr = "";
    // char prev = '\n';
    // for(int i = 0; i < str.size();i ++) {
    //     if(str[i] == prev) {
    //         curr.push_back(str[i]);
    //     } else {
    //         curr = str[i];
    //     }
    //     s.insert(curr);
    //     prev = str[i];
    // }

    // cout << s.size() << '\n';

    int n; cin >> n;
    string str; cin >> str;
    vector<int> longs(26);

    char prev = '\n';
    int curr = -1;
    int currlength = -1;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == prev) {
            currlength++;
        } else {
            curr = str[i] - 'a';
            currlength = 1;
        }
        longs[curr] = max(longs[curr],currlength);
        prev = str[i];
    }

    cout << reduce(longs.begin(), longs.end()) << '\n';

    return 0;
}