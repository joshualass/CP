#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

bool distance(int x1, int y1, int x2, int y2, int r) {
    return r * r >= (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int l, w, n, r; cin >> l >> w >> n >> r;
    int right = l/2;
    int left = l / -2;
    int up = w/2;
    int down = w/-2;
    vector<int> cranes(n);
    int possible = 0;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        int num = 0;
        if(distance(x,y,left,0, r)) num |= 1;
        if(distance(x,y,right,0,r)) num |= 2;
        if(distance(x,y,0,up,r)) num |= 4;
        if(distance(x,y,0,down,r)) num |= 8;
        cranes[i] = num;
        possible |= num;
    }
    if(possible != 15) {
        cout << "Impossible";
        return 0;
    }
    for(int a = 0; a < n; a++) {
        if(cranes[a]) {
            cout << 1;
            return 0;
        }
    }
    for(int a = 0; a < n; a++) {
        for(int b = a + 1; b < n; b++) {
            
        if(cranes[a]) {
            cout << 1;
            return 0;
        }
        }
    }

    cout << 1;
    return 0;
}