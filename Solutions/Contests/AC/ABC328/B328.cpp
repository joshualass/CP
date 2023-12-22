#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void add(int i, vector<int> &cnts) {
    while(i) {
        cnts[i % 10]++;
        i /= 10;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        int days; cin >> days;
        for(int j = 1; j <= days; j++) {
            vector<int> cnts(10);
            add(j,cnts);
            add(i,cnts);
            if(count(cnts.begin(),cnts.end(),0) == 9) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
    
    return 0;
}