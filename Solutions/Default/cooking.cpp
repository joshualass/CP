//https://atcoder.jp/contests/abc204/tasks/abc204_d?lang=en
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int N = 1e5 + 1;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    bitset<N> reachable{};
    reachable[0] = 1;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        sum += num;
        reachable |= reachable << num;
    }
    int diff = INT_MAX;
    for(int i = 0; i < N; i++) {
        if(reachable[i]) {
            diff = min(diff,abs(sum/2-i));
        }
    }
    cout << sum / 2 + diff + (sum & 1) << "\n";

    return 0;
}