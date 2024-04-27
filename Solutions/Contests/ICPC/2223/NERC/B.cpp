#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll prefs[10][100][1000];
ll idxs[100][1000]; //for record i, the value at each index
ll ridxs[100][1000]; //for record i, the index of each value
ll hashes[10][1000]; //for hash i, 
int parents[1000];

void dnc(vector<pair<int,int>> lr, int p) {

    for(int i = lr[0].first; i <= lr[0].second; i++) {
        bool ok = 1;
        int pivot = idxs[0][i];
        for(int j = 0; j < 10; j++) {
            
            for(int k = 1; k < lr.size(); k++) {
                int prev1 = prefs[j][k-1][i-1] - prefs[j][k-1][l-1];
                int curr1 = prefs[j][k][i-1] - prefs[j][k][l-1];
                int prev2 = prefs[j][k-1][r] - prefs[j][k-1][i];
                int curr2 = prefs[j][k][r] - prefs[j][k][i];
                // cout << "p : " << prev << " c : " << curr << '\n';
                if(i == 4) {
                    cout << "p1 : " << prev1 << " p2 : " << prev2 << " curr1 : " << curr1 << " curr2 : " << curr2 << '\n';
                    if(prev1 == curr1 && prev2 == curr2 || prev1 == curr2 && prev2 == curr1) {

                    } else {
                        cout << "NOT OK /!\\\n";
                        ok = 0;
                    }

                }
            }
        }
        if(((i - l) & 1) == 0) ok = 0;
        if(l == r) ok = 1;
        if(ok) {

            parents[idxs[i]] = p;
            if(l <= i - 1) {
                dnc(l,i-1,i,K);
            }
            if(i+1 <= r) {
                dnc(i+1,r,i,K);
            }
            return;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    srand(chrono::steady_clock::now().time_since_epoch().count());
    int n, k; cin >> n >> k;
    memset(prefs,0,sizeof(prefs));
    memset(idxs,0,sizeof(idxs));
    memset(ridxs,0,sizeof(ridxs));
    memset(hashes,0,sizeof(hashes));
    memset(parents,0,sizeof(parents));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 1000; j++) {
            hashes[i][j] = rand();
        }
    }    
    
    for(int i = 0; i < k; i++) {
        for(int j = 1; j <= n; j++) {
            int num; cin >> num;
            idxs[i][j] = num;
            ridxs[i][num] = j;
            for(int k = 0; k < 10; k++) {
                prefs[k][i][j] = prefs[k][i][j-1] + hashes[k][num];
                // cout << "pkij? " << prefs[k][i][j] << '\n';
            }
        }
    }

    vector<pair<int,int>> lr(k);
    for(auto &x : lr) x = {1,n};

    dnc(lr,-1);

    for(int i = 1; i <= n; i++) {
        cout << parents[i] << " \n"[i == n];
    }

    return 0;
}