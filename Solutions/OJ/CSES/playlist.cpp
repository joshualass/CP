#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    map<int,vector<int>> m;
    int best = 0;
    int start = -1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(m.find(num) == m.end()) {
            m[num] = {i};
        } else {
            start = max(start,m[num][m[num].size() - 1]);
            m[num].push_back(i);
        }
        // cout << "i : " << i << " start: " << start << "\n";
        best = max(best, i - start);
    }
    cout << best << "\n";
    return 0;
}