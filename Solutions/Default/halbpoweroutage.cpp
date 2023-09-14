#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<pair<ld,ld>> solve(int n, vector<ld> v) {
    if(n == 2) {
        if(v[0] == v[1]) {
            return {{0,0},{v[0],0},{0,0}};
        } else {
            return {{-1,-1}};
        }
    } 
    ld below = 0;
    ld above = 0;
    for(ld x : v) {
        above += x;
    }
    //try to make segment at i the connecting segment
    int index = -1;
    for(int i = 0; i < n; i++) {
        if(abs(above - v[i] - below) <= v[i]) {
            
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ld> v(n);
    for(ld &x: v) cin >> v;
    solve();

    return 0;
}