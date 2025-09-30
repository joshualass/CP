#include "testlib.h"
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main(int args_length, char* args[]) {

    registerGen(args_length, args, 1);
    
    int n = stoi(args[1]);
    int k = stoi(args[2]);
    int ub = stoi(args[3]);

    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        a[i] = rnd.next(ub) + 1;
    }

    cout << n << " " << k << '\n';
    for(int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }

    return 0;
}
