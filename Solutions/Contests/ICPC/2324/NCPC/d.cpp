#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool is_better(vector<int>& a, vector<int>& b) {
    //is a better than b
    int wins = 0;
    int cnt = 0;
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            if(a[i] > b[j]) {
                wins ++;
            }
            cnt += a[i] != b[j];
        }
    }
    return wins >= cnt - wins && cnt != 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> dice(3, vector<int>(6));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 6; j++){
            cin >> dice[i][j];
        }
    }
    int ans = -1;
    for(int i = 0; i < 3; i++){
        bool is_valid = true;
        for(int j = 0; j < 3; j++){
            if(i == j){
                continue;
            }
            is_valid = is_valid & is_better(dice[i], dice[j]);
        }
        if(is_valid) {
            ans = i + 1;
            break;
        }
    }
    if(ans == -1){
        cout << "No dice\n";
    }
    else {
        cout << ans << "\n";
    }

    return 0;
}