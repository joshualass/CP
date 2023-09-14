#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<ll> v(n);
        for(ll &x: v) cin >> x;
        sort(v.begin(), v.end());

        vector<ll> nums(3);
        nums[1] = v[0];
        nums[2] = v[1];
        ll l = LLONG_MAX;
        for(int i = 2; i < n; i++) {
            nums[0] = nums[1];
            nums[1] = nums[2];
            nums[2] = v[i];

            l = min(l, nums[2] - nums[0]);
        }
        cout << l << '\n';
    }

    return 0;
}