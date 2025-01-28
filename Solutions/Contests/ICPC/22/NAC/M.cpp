#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> cur(5, 0);
    vector<vector<int>> a;
    int base = 5;
    for(int i = 0; i < base; i++){
        vector<int> tmp(5, 0);
        tmp[0] = i;
        a.push_back(tmp);
    }
    for(int i = 1; i < 5; i++){
        vector<vector<int>> tmpa;
        for(int j = 0; j < base; j++){
            for(int k = 0; k < a.size(); k++){
                vector<int> tmp = a[k];
                tmp[i] = j;
                tmpa.push_back(tmp);
            }
            reverse(a.begin(), a.end());
        }
        a = tmpa;
    }
    vector<string> ans;
    for(int i = 0; i < a.size() - 1; i++){
        vector<int> x = a[i], y = a[i + 1];
        string s(10, ' ');
        for(int j = 0; j < 5; j++) {
            s[j * 2] = 'a' + x[j], s[j * 2 + 1] = 'a' + x[j];
        }
        ans.push_back(s);
        for(int j = 0; j < 5; j++){
            s[j * 2] = 'a' + x[j], s[j * 2 + 1] = 'a' + y[j];
        }
        ans.push_back(s);
    }
    // for(int i = 0; i < a.size(); i++){
    //     for(int j = 0; j < i - 1; j++) {
    //         int diff = 0;
    //         for(int k = 0; k < 10; k++){
    //             diff += ans[i][k] != ans[j][k];
    //         }
    //         if(diff == 1) cout << "1 DIFF : " << i << " " << j << " " << ans[i] << " " << ans[j] << "\n";
    //     }
    // }
    for(int i = 0; i < n; i++){
        cout << ans[i] << "\n";
    }

    return 0;
}