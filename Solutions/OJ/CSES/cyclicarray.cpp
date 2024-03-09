#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;

int lifts[N*2][20]; // do you even lift lil bro?

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    int hi = -1;
    ll curr = 0;
    for(int i = 0; i < 2 * n; i++) {
        while((hi < 2 * n) && (curr + v[(hi + 1) % n] <= k)) {
            curr += v[(hi + 1) % n];
            hi++;
        }
        lifts[i][0] = hi + 1;
        curr -= v[i % n];
    }

    // for(int i = 0; i < 16; i++) {
    //     cout << lifts[i][0] << " ";
    // }
    for(int p = 1; p < 20; p++) {
        for(int i = 0; i < 2 * n; i++) {
            int move = lifts[i][p-1];
            if(move < n * 2) {
                move = lifts[move][p-1];
            }
            lifts[i][p] = move;
        }
    }

    // for(int i = 0; i < 2 * n; i++) {
    //     cout << "\ni: " << i << " ";
    //     for(int p = 0; p < 20; p++) {
    //         cout << lifts[i][p] << " ";
    //     }
    // }
    int best = INT_MAX;
    int idx = -1;
    for(int i = 0; i < n; i++) {
        int p = 19;
        int moves = 0;
        int a = i;
        while(p >= 0) {
            // cout << "a: " << a << " " << moves << "\n";
            if(lifts[a][p] < i + n) {
                a = lifts[a][p];
                moves += 1 << p;
            }
            p--;
        }
        // best = min(best, moves+1);
        if(moves + 1 < best) {
            best = moves+1;
            idx = i;
        }
    }
    cout << best << "\n";
    // cout << idx;
    return 0;
}
