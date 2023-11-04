#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef __int128_t lll;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll L, R; cin >> L >> R;

    lll l = L;
    lll r = R;



}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<array<lll,3>>> ranges(64);

    for(int i = 2; i < 64; i++) {
        //i is the current f(x)
        //now we just need to find the values where g(x) changes
        //numbers are bounded by 1 << i and (1 << (i + 1)) - 1
        lll low = (((lll) 1) << i);
        lll lo = 1;
        ll pow = 0;

        lll stop = (((lll)1 )<< (i + 1));

        while(lo < stop) {
            lll loidx = max(lo,low);
            lll hiidx = min(stop, lo * 2);

            if(hiidx > loidx) {
                ranges[i].push_back(array<lll,3>{{loidx,hiidx,pow}});
            }
            lo *= i;
            pow++;
        }


    }    

    for(int i = 0; i < 10; i++) {
        cout << "i: " << i << " ";
        for(auto j : ranges[i]) {
            cout << "[" << (ll) j[0] << ", " << (ll) j[1] << ", " << (ll) j[2] << "] ";
        }


        cout << '\n';
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}