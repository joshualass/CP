#include <bits/stdc++.h>
using namespace std;

int main() {
    
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
    
    for(int i = 0; i < digs.size(); i++) {
        int s = i + digs[i] + digs[digs[i]] + digs[digs[digs[i]]] + digs[digs[digs[digs[i]]]] + digs[digs[digs[digs[digs[i]]]]];
        if(s == 2024) {
            cout << "s : " << s << '\n';
        }
    }

    return 0;
}