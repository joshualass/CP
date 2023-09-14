#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int r, c; cin >> r >> c;
        cout << "? 1 1" << endl;
        int distance; cin >> distance;
        if(r == 1 || c == 1) { 
            if(r == 1) {
                cout << "! " << 1 << " " << 1 + distance << endl;
            } else {
                cout << "! " << 1 + distance << " " << 1 << endl;
            }
            continue;
        }
        cout << "? " << min(r,distance + 1) << " " << min(c, distance + 1) << endl;
        int distance2; cin >> distance2;
        if(distance2 == 0) {
            cout << "! " << min(r,distance + 1) << " " << min(c, distance + 1) << endl;
            continue;
        }
        cout << "? " << min(r, distance + 1) - 1 << " " << min(c, distance + 1) << endl;
        int distance3; cin >> distance3;
        if(distance3 < distance2) {
            cout << "! " << min(r,distance+1) - distance2 << " " << min(c, distance + 1) << endl;
        } else {
            cout << "! " << min(r,distance+1) << " " << min(c, distance + 1) - distance2 << endl;
        }
    }

    return 0;
}