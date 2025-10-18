#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/**
 * 2D Fenwick Tree implementation.
 * Note that all cell locations are zero-indexed
 * in this implementation.
 */
template <typename T> class BIT2D {
  private:
	const int n, m;
	vector<vector<T>> bit;

  public:
	BIT2D(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1)) {}

	/** adds val to the point (r, c) */
	void add(int r, int c, T val) {
		r++, c++;
		for (; r <= n; r += r & -r) {
			for (int i = c; i <= m; i += i & -i) { bit[r][i] += val; }
		}
	}

	/** @returns sum of points with row in [0, r] and column in [0, c] */
	T rect_sum(int r, int c) {
		r++, c++;
		T sum = 0;
		for (; r > 0; r -= r & -r) {
			for (int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
		}
		return sum;
	}

	/** @returns sum of points with row in [r1, r2] and column in [c1, c2] */
	T rect_sum(int r1, int c1, int r2, int c2) {
		return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
		       rect_sum(r1 - 1, c1 - 1);
	}
};

ll count_validhops_leq(vector<vector<int>> &grid, vector<vector<array<int,2>>> &coords, int k) {
    int r = grid.size(), c = grid[0].size();
    BIT2D<int> bit2d(r, c);

    ll res = 0;

    for(int i = 0; i < coords.size(); i++) {
        for(auto [x, y] : coords[i]) {
            bit2d.add(x,y,1);
        }

        for(auto [x, y] : coords[i]) {
            int lox = max(0, x - k), hix = min(r - 1, x + k);
            int loy = max(0, y - k), hiy = min(c - 1, y + k);
            int sum = bit2d.rect_sum(lox, loy, hix, hiy);
            res += (hix - lox + 1) * (hiy - loy + 1) - sum;
        }

        // cout << "k : " << k << '\n';

        // cout << "res : " << res << '\n';

        for(auto [x, y] : coords[i]) {
            bit2d.add(x,y,-1);
        }
    }

    return res;

}

void solve() {
    
    int r, c; cin >> r >> c;
    ll k; cin >> k;

    vector<vector<int>> grid(r, vector<int>(c));

    vector<vector<array<int,2>>> coords(r * c);
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {

            int num; cin >> num;
            num--;
            grid[i][j] = num;
            coords[num].push_back({i,j});

        }
    }

    int l = 1, hi = max(r,c);

    while(l != hi) {
        int m = (l + hi) / 2;
        ll cnt = count_validhops_leq(grid, coords, m);

        if(cnt >= k) {
            hi = m;
        } else {
            l = m + 1;
        }

    }

    cout << l << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}