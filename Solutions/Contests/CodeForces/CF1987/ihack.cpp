#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll a[5005], p[5005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll i, j;

	ll t = 1;
	cout << t << '\n';

	for (ll tt = 1; tt <= t; tt++)
	{
		ll n = 5000;
		for (i = 1; i <= n; i++)
			a[i] = i;
		for (i = 2; i <= n; i++)
			p[i] = i - 1;

		cout << n << '\n';
		for (i = 1; i <= n; i++)
			cout << a[i] << (i == n ? '\n' : ' ');
		for (i = 2; i <= n; i++)
			cout << p[i] << (i == n ? '\n' : ' ');
	}
}