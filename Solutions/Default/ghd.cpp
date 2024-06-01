#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
mt19937 rng;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    return 0;
}