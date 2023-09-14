#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dp[30001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        int num;cin >> num;
        v[i] = num;
    }
    for (int c = 0; c <= 30000; c++) {
        dp[c] = -1;
    }
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 30000; j++) {
            if (j - v[i] >= 0) {
                int before = dp[j - v[i]];
                if (before == -2) {
                    dp[j] = -2;
                } else if (before != -1) {
                    if (dp[j] == -1) {
                        dp[j] = i;
                    } else {
                        dp[j] = -2;
                    }
                }
            }
        }
    }

    // for (int i = 0; i <= 15; i++) {
    //     cout << dp[i] << " ";
    // }
    // cout << "\n";
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        // num++;
        vector<int> path(0);
        if(dp[num] == -1) {
            cout << "Impossible\n";
            continue;
        }
        int index = num;
        bool amb = false;
        while(num != 0) {
            if(dp[num] == -2) {
                amb = true;
                break;
            } 
            path.push_back(dp[num]);
            num -= v[dp[num]];
        }
        sort(path.begin(),path.end());
        if(amb) {
            cout << "Ambiguous\n";
        } else {
            string out = "";
            for(int x : path) {
                out += to_string(++x) + " ";
            }
            cout << out << "\n";
        }
    }

    return 0;
}