#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<map<int,int>> v(5);
    vector<set<int>> sets(5);

    int t, c; cin >> t >> c;

    set<int> targets;

    for(int i = 0; i < t; i++) {
        int num; cin >> num;
        targets.insert(num);
    }

    string str; cin >> str;

    int idx = 0;
    for(int i = 0; i < c; i++) {
        switch(str[i]) {
            case 'L' : idx--; break;
            case 'R' : idx++; break;
            case 'F' : 
                for(int j = 0; j < 5; j++) {
                    v[j][idx + j - 2]++;
                    if(targets.find(idx + j - 2) != targets.end()) {
                        sets[j].insert(idx + j - 2);
                    }
                }
                break;
        }
    }

    int ans = sets[2].size(); //no changes in commands

    set<int> curr;
    idx = 0;

    for(int i = 0; i < c; i++) {
        switch(str[i]) {
            case 'L' : 
                //we try firing instead of going left
                // cout << "i : " << i << " L1 : " << ((int)sets[3].size() + (sets[3].find(idx) == sets[3].end())) << '\n';
                ans = max(ans, (int)sets[3].size() + (sets[3].find(idx) == sets[3].end() && targets.find(idx) != targets.end()));
                //we try going right intead of going left
                // cout << "i : " << i << " L2 : " << (int)sets[4].size() << '\n';
                ans = max(ans, (int)sets[4].size());
                idx--;
                break;
            case 'R' :
                //we try firing instead of going right
                // cout << "i : " << i << " R1 : " << ((int)sets[1].size() + (sets[1].find(idx) == sets[1].end())) << '\n';
                ans = max(ans, (int)sets[1].size() + (sets[1].find(idx) == sets[1].end() && targets.find(idx) != targets.end()));
                //we try going left instead of going right
                // cout << "i : " << i << " R2 : " << (int)sets[0].size() << '\n';
                ans = max(ans, (int)sets[0].size());
                idx++;
                break;
            case 'F' :
                //if we change from the fire command, we should update the other ones first, then update current
                for(int j = 0; j < 5; j++) {
                    int upd_idx = idx + j - 2;
                    v[j][upd_idx]--;
                    if(v[j][upd_idx] == 0 && curr.find(upd_idx) == curr.end()) {
                        sets[j].erase(upd_idx);
                    }
                }
                //we try going left instead of firing
                ans = max(ans, (int)sets[1].size());
                //we try going right instead of firing
                ans = max(ans, (int)sets[3].size());
                //then we update current
                curr.insert(idx);
                for(int j = 0; j < 5; j++) {
                    if(targets.find(idx) != targets.end()) {
                        sets[j].insert(idx);
                    }
                }

        }
    }
    cout << ans << '\n';

    return 0;
}