#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;



void Z(const string S, vector<int> &z) {
    z.assign(sz(S), 0);
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
}

void solve() {
    
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> z, st(n * 2);
    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--;
        Z(s.substr(l, r - l), z);
        z[0] = r - l;
        ll res = 0;
        int pt = 0;
        for(int i = l; i < r; i++) {
            while(z[i-l] == 0 && pt && i >= st[pt-1]) pt--;
            if(z[i-l]) {
                st[pt++] = i + z[i-l];
            }
            res += pt;
        }
        cout << res << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}