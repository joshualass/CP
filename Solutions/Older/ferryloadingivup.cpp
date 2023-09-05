#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-->0) {

        int l, m;
        cin >> l >> m;
        l *= 100;
        queue<int> lefts;
        queue<int> rights;
        for(int i = 0; i < m; i++) {
            string side;
            int size;
            cin >> size >> side;
            if(side == "left") {
                lefts.push(size);
            } else {
                rights.push(size);
            }
        }

        int leftcount = 0;
        while(lefts.size()) {
            int remaining = l;
            leftcount++;
            while(lefts.size() && lefts.front() <= remaining) {
                remaining -= lefts.front();
                lefts.pop();
            }
        }
        int rightcount = 0;
        while(rights.size()) {
            int remaining = l;
            rightcount++;
            while(rights.size() && rights.front() <= remaining) {
                remaining -= rights.front();
                rights.pop();
            }
        }
//        cout << "leftcount: " << leftcount << " rightcount: " << rightcount << '\n';
        cout << max(leftcount * 2 - 1, rightcount * 2) << '\n';
    }

    return 0;
}