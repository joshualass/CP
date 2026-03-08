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

vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi match(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        string pattern, text;
        getline(cin, pattern);
        if(cin.eof()) break;
        getline(cin, text);
        // cout << "text : " << text << " pattern : " << pattern << endl;
        auto res = match(text, pattern);
        for(auto x : res) cout << x << " ";
        cout << '\n';
    }

    return 0;
}
