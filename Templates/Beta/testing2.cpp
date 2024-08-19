#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c, d; cin >> a >> b >> c >> d;
	vector<ll> e(b);
	for(ll &f : e) cin >> f;
	ll sum = accumulate(e.begin(), e.end(), 0LL);

	cout << "sum : " << sum << " do things : " << sum - b * d << '\n';

    return 0;
}