#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 200000;

int bosses[N][32];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        fill(begin(bosses[i]), begin(bosses[i]) + 32, -1);
    }
    for(int i = 1; i < n; i++) {
        int num; cin >> num;
        num--;
        bosses[i][0] = num;
    }
    
    for(int p = 1; p < 32; p++) {
        for(int i = 0; i < n; i++) {
            int move = bosses[i][p-1];
            if(move != -1) {
                bosses[i][p] = bosses[move][p-1];
            }
        }
    }
    
    for(int i = 0; i < q; i++) {
        int x, k; cin >> x >> k;
        x--;
        int p = 0;
        while(k != 0) {
            if(x == -1) {
                break;
            }
            if(k & 1) {
                x = bosses[x][p];
            }
            k >>= 1;
            p++;
        }
        cout << (x == -1 ? x : ++x) << "\n";
    }
    

    return 0;
}