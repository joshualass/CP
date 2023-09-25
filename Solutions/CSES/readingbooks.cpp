#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#ifdef __APPLE__
	#define err(args...) {error(args);}
	template<typename... Args>
	void error(Args... args) {
		((cerr << args << ' '),...);
	}
	#define errln(args...) {errorln(args);}
	template<typename... Args>
	void errorln(Args... args) {
		((cerr << args << ' '),...);
		cerr << '\n';
	}
#else 
	#define err(...)
	#define errln(...)
#endif

int main() {
    clock_t sTime = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // int n; cin >> n;
    // vector<ll> v(n);
    // ll sum = 0;
    // for(auto &x: v) {cin >> x; sum += x;}
    // sort(v.begin(),v.end());
    // cout << max(sum,v[n-1]*2) << "\n";
    int n; cin >> n;
    vector<ll> v(n);
    ll sum = 0;
    for(auto &x: v) {cin >> x; sum += x;};
    cout << max(sum,*max_element(v.begin(),v.end()) * 2) << endl;

    // int Runtime=(double)(clock() - sTime) / CLOCKS_PER_SEC * 1000;
    // cout << Runtime << "\n";

    return 0;
}