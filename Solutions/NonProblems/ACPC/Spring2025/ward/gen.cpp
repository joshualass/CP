#include "testlib.h"
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main(int args_length, char* args[]) {

    registerGen(args_length, args, 1);

    int n = stoi(args[1]);
    int lowx = stoi(args[2]);
    int lowy = stoi(args[3]);
    int hix = stoi(args[4]);
    int hiy = stoi(args[5]);

    cout << n << '\n';

    set<array<int,2>> pts;
    for(int i = 0; i < n; i++) {
        while(1) {
            int x = rnd.next(lowx, hix), y = rnd.next(lowx, hiy);
            if(pts.count({x,y}) == 0) {
                cout << x << " " << y << '\n';
                pts.insert({x,y});
                break;
            }
        }
    }

    return 0;
}
