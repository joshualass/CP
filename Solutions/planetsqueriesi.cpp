#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int lifts[200000][32];

void printAdj() {
    cout << " --- adjlist --- \n";
    for(int i = 0; i < 4; i++) {
        cout << "i - " << i << ':';
        for(int j = 0; j < 32; j++) {
            cout << lifts[i][j] << " ";
        }
        cout << "\n";
    }
}

void solve(int idx, int pow) {
    int move = lifts[idx][pow-1];
    lifts[idx][pow] = lifts[move][pow-1];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        lifts[i][0] = num;
    }
    for(int pow = 1; pow < 32; pow++) {
        for(int i = 0; i < n; i++) {
            solve(i, pow);
        }
    }
    
    for(int i = 0; i < q; i++) {
        int x, k; cin >> x >> k;
        x--;
        int pow = 0;
        while(k != 0) {
            if(k % 2 == 1) {
                x = lifts[x][pow];
            }
            k /= 2;
            pow++;
        }
        cout << ++x << "\n";
    }

    return 0;
}