#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x) {
    cout << " --- vector --- \n";
    for(int y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int P; cin >> P;
    for(int b = 1; b <= P; b++) {
        int num; cin >> num;
        vector<int> v(14);
        for(int i = 1; i <= 12; i++) {
            cin >> v[i];
        }
        // printV(v);
        int count = 0;
        for(int r = 1; r <= 12; r++) {
            for(int l = 1; l <= r; l++) {
                int least = INT_MAX;
                for(int i = l; i <= r; i++) {
                    least = min(least,v[i]);
                }
                bool flag = true;
                if(v[l-1] >= least) {
                    flag = false;
                }
                if(v[r+1] >= least) {
                    flag = false;
                }
                if(flag) {
                    count++;
                }
                // bool flag = true;
                // if(v[l-1] >= v[l]) {
                //     flag = false;
                // }
                // if(v[r+1] >= v[r]) {
                //     flag = false;
                // }
                // for(int i = l + 1; i < r; i++) {
                //     if(v[i] < min(v[l],v[r])) {
                //         flag = false;
                //     }
                // }
                // if(flag) {
                //     count++;
                //     cout << l << " " << r << "\n";
                // }
            }
        }
        cout << b << " " << count << "\n";
    }

    return 0;
}