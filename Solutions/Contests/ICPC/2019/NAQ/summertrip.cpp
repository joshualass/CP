#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; cin >> str;
    int n = str.size();

    vector<set<int>> v(26);

    for(int i = 0; i < n; i++) {
        v[str[i] -'a'].insert(i);
    }

    int ans = 0;
    for(int start = 0; start < n; start++) {
        int start_index = -1;
        int start_letter = str[start] - 'a';
        // cout << "start letter : "
        if(v[start_letter].upper_bound(start) != v[start_letter].end()) {
            start_index = *v[start_letter].upper_bound(start);
        }
        for(int end = 0; end < 26; end++) {
            if(end != start_letter) {
                set<int>::iterator it = v[end].upper_bound(start);
                if(it != v[end].end()) {
                    if(start_index == -1 || *it < start_index) {
                        // cout << "start : " << start << " end : " << end << '\n';
                        ans++;
                    }
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}