#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//next number we are able to make, at which index
void addQueue(int poss, int idx, vector<queue<array<int,2>>> &d, int n, vector<bool> &vis) {
    if(vis[poss]) return;
    vis[poss] = 1;
    for(int i = 0; i + poss <= n; i++) { //i is what other number we can make
        int dest = i ^ poss;
        d[i].push({dest, idx}); //if we are able to make needed with MEX, then we can make 
    }
}

bool mexvis[5001];

//highest MEX is n. Each number in array is not able to contribute > 1. 
void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<bool> vis(n + 1);
    vector<queue<array<int,2>>> d(n + 1);

    addQueue(0,-1,d,n,vis);
    
    for(int i = 0; i < n; i++) {
        memset(mexvis,0,sizeof(mexvis));
        int currmex = 0;
        for(int j = i; j >= 0; j--) {
            mexvis[a[j]] = 1;
            while(mexvis[currmex]) currmex++;
            while(d[currmex].size() && d[currmex].front()[1] < j) {
                array<int,2> a = d[currmex].front();
                d[currmex].pop();
                addQueue(a[0], i, d, n, vis);
            }
        }
    }

    for(int i = n; i >= 0; i--) {
        if(vis[i]) {
            cout << i << '\n';
            return;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}