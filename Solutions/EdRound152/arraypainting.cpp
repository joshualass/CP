#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
void printV(const vector<bool> &x) {
    cout << " --- vector --- \n";
    for(bool y : x) {
        cout << y << " ";
    }
    cout << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    vector<bool> painted(n,false);
    for(int &x: v) cin >> x;
    if(n == 1) {
        cout << "1\n";
        return 0;
    }
    int coins = 0;
    //fill all 2's
    for(int i = 1; i < n-1; i++) {
        if(!painted[i] && v[i] == 2 && !painted[i-1] && !painted[i+1]) {
            coins++;
            painted[i] = true;
            for(int t = i - 1; t >= 0; t--) {
                if(painted[t]) {
                    break;
                }
                painted[t] = true;
                if(v[t] == 0) {
                    break;
                }
            }
            for(int t = i + 1; t < n; t++) {
                if(painted[t]) {
                    break;
                }
                painted[t] = true;
                if(v[t] == 0) {
                    break;
                }
            }
        }
    }
    // printV(painted);
    
    //after first painting, try 1's
    bool prev1 = false;
    vector<bool> carry(n, false);
    for(int i = 0; i < n; i++) {
        if(!painted[i] && v[i] >= 1) { //paint on 1
            // cout << "encounter 1 i: " << i << "\n";
            coins++;
            bool flowleft = (i != 0 && !painted[i-1]);
            int r = i + 1;
            painted[i] = true;
            for(; r < n; r++) {
                if(painted[r]) {
                    break;
                }
                if(v[r] >= 1) {
                    painted[r] = true;
                } else {
                    break;
                }
            }
            if(flowleft) {
                painted[i-1] = true;
            } else {
                painted[r] = true;
            }
        } else {
            prev1 = false;
        }
    }
    //fill 0's
    for(int i = 0; i < n; i++) {
        if(!painted[i]) {
            // cout << "painting remaining i: " << i << "\n";
            coins++;
        }
    }
    cout << coins << "\n";
    return 0;
}
