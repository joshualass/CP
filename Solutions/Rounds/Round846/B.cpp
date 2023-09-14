#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    while(T-->0) {
        vector<ll> v(0);
        int N;
        cin >> N;
        ll sum = 0;
        ll best = 1;
        ll total = 0;
        for(int i = 0; i < N; i++) {
            ll num;
            cin >> num;
            v.push_back(num);
            sum += num;
        }
        for(int i = 0; i < N-1; i++) {
            total += v[i];
            best = max(best,gcd(total,sum-total));
//            cout << best << " " << total << " " << sum-total << "\n";
        }
        cout << best << "\n";
    }

    return 0;
}