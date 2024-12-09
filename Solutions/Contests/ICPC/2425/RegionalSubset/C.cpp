#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n;
    cin >> k >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    set<string> ans;
    for(int i = 0; i < (1 << a[0].size()); i++){
        string seq;
        for(int j = 0; j < a[0].size(); j++){
            if(i & (1 << j)) {
                seq.push_back(a[0][j]);
            }
        }
        if(seq.size() != k){
            continue;
        }
        bool is_valid = true;
        for(int j = 0; j < n; j++){
            int ptr = 0;
            for(int k = 0; k < a[j].size(); k++){
                if(ptr != seq.size() && a[j][k] == seq[ptr]) {
                    ptr ++;
                }
            }
            if(ptr != seq.size()) {
                is_valid = false;
            }
        }
        if(is_valid){
            ans.insert(seq);
        }
    }
    cout << ans.size() << "\n";
    for(auto i = ans.begin(); i != ans.end(); i++){
        cout << *i << "\n";
    }

    return 0;
}