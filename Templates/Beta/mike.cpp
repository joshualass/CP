#include <bits/stdc++.h>
using namespace std;

signed main() {
    
    vector<int> digs(2025);
    for(int i = 0; i < digs.size(); i++) {
        int t = i;
        int s = 0;
        while(t) {
            s += t % 10;
            t /= 10;
        }
        digs[i] = s;
    }

    // for(int x : digs) cout << x << " ";
    
    for(int i = 0; i < digs.size(); i++) {
        int s = i + digs[i] + digs[digs[i]] + digs[digs[digs[i]]] + digs[digs[digs[digs[i]]]] + digs[digs[digs[digs[digs[i]]]]];
        // for(int j = 2020; j <= 2030; j++) {
        //     if(s == j) {
        //         cout << "j : " << j << " s : " << s << " i : " << i << '\n';
        //     }
        // }
        if(s == 2024) {
            cout << "s : " << s << '\n';
        }
    }

    return 0;
}