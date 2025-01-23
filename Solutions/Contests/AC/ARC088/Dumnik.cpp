#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair

const int N = 100100;
int n;
vector<int> g[N];
int dp[N];
int m;

bool solve(int v, int par) {
	vector<int> a;
	if ((int)g[v].size() & 1) a.push_back(0);
	for (int u : g[v]) {
		if (u == par) continue;
		if (!solve(u, v)) return false;
		if (dp[u] != -1)
			a.push_back(dp[u] + 1);
	}
	sort(a.begin(), a.end());
/*
	printf("%d :", v);
	for (int x : a)
		printf(" %d", x);
	printf("\n");
*/
	if ((int)a.size() & 1) {
		int l = -1, r = (int)a.size();
		while(r - l > 1) {
			int x = (l + r) / 2;
			int p1 = 0, p2 = (int)a.size() - 1;
			bool ok = true;
			while(p1 < p2) {
				if (p1 == x) p1++;
				if (p2 == x) p2--;
				if (a[p1] + a[p2] > m) {
					ok = false;
					break;
				}
				p1++;
				p2--;
			}
			if (ok)
				r = x;
			else
				l = x;
		}
		if (r == (int)a.size()) return false;
		dp[v] = a[r];
		return true;
	} else {
		for (int i = 0; i < (int)a.size(); i++)
			if (a[i] + a[(int)a.size() - 1 - i] > m)
				return false;
		dp[v] = -1;
		return true;
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	// scanf("%d", &n);
    n = 1e5;
	for (int i = 1; i < n; i++) {
		// int v, u;
		// scanf("%d%d", &v, &u);
		// v--;u--;
		// g[v].push_back(u);
		// g[u].push_back(v);
        g[i].push_back(i-1);
        g[i-1].push_back(i);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += (int)g[i].size() & 1;
	printf("%d ", ans / 2);
	int l = 0, r = n;
	while(r - l > 1) {
		m = (l + r) / 2;
		if (solve(0, -1))
			r = m;
		else
			l = m;
	}
	printf("%d\n", r);

	return 0;
}
