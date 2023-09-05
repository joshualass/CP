#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    cin >> line;

    int U = 0;
    int D = 0;
    int P = 0;

    char prevU = line[0];
    char prevD = line[0];
    char prevP = line[0];
    for(int i = 1; i < line.length(); i++) {
        if(prevU == 'U') {
            if(line[i] == 'D') {
                U += 2;
            }
        } else {
            U++;
        }
        if(prevD == 'D') {
            if(line[i] == 'U') {
                D += 2;
            }
        } else {
            D++;
        }
        if(line[i] != prevP) {
            P++;
        }

        prevU = 'U';
        prevD = 'D';
        prevP = line[i];
    }
    cout << U << '\n' << D << '\n' << P;
    return 0;
}