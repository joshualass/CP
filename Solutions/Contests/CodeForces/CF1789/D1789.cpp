#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

// cout << "start\n";
// cout << "my bitset : ";
// for(int i = 0; i < n; i++) {
//     cout << bsa[i];
// }
// cout << '\n';
// cout << "target bitset : ";
// for(int i = 0; i < n; i++) {
//     cout << bsb[i];
// }
// cout << '\n';

void solve() {

    int n; cin >> n;
    string a, b; cin >> a >> b;
    bitset<2000> bsa{};
    bitset<2000> bsb{};

    //already matching which includes all zero case.  
    if(a == b) {
        cout << "0\n";
        return;
    }

    //one of them is empty while the other is not. never possible. 
    if(((bool) count(a.begin(), a.end(), '1')) != ((bool) count(b.begin(), b.end(), '1'))) {
        cout << "-1\n";
        return;
    }

    for(int i = 0; i < n; i++) {
        if(a[i] == '1') {
            bsa[i] = 1;
        }
        if(b[i] == '1') {
            bsb[i] = 1;
        }
    }


    //implementation is tricky

    vector<int> ops;

    //first ensure that the earliest set bit in b is set in a. This will be our pivot. 
    int earliestb = -1;
    for(int i = 0; i < n; i++) {
        if(bsb[i]) {
            earliestb = i;
            break;
        }
    }

    if(bsa[earliestb] == 0) {
        int earliesta = -1;
        for(int i = 0; i < n; i++) {
            if(bsa[i]) {
                earliesta = i;
                break;
            }
        }
        int shift = earliestb - earliesta;
        assert(shift);
        // cout << "shift : " << shift << '\n';
        ops.push_back(shift);
        if(shift > 0) {
            bsa ^= bsa << shift;
        } else {
            bsa ^= bsa >> (-shift);
        }
        for(int i = n; i < 2000; i++) {
            bsa[i] = 0;
        }
    }

    //second, clear set bits before the earliest set bit in b.
    while(1) { // given that bit is set at earliest b. 

        int latesta = -1;
        for(int i = earliestb - 1; i >= 0; i--) {
            if(bsa[i]) {
                latesta = i;
                break;
            }
        }

        // cout << "latesta : " << latesta << '\n';

        if(latesta != -1) {
            int last = -1;
            for(int i = n - 1; i >= 0; i--) {
                if(bsa[i]) {
                    last = i;
                    break;
                }
            }
            int shift = latesta - last;
            assert(shift);
            // cout << "shift : " << shift << '\n';
            ops.push_back(shift);
            if(shift > 0) {
                bsa ^= bsa << shift;
            } else {
                bsa ^= bsa >> (-shift);
            }
            for(int i = n; i < 2000; i++) {
                bsa[i] = 0;
            }
        } else {
            break;
        }

    }

    //Now, all bits <= earliest b are correct. Now we fix all bits after earliestb
    while(1) {

        int earliestdiff = -1;
        for(int i = earliestb + 1; i < n; i++) {
            if(bsa[i] != bsb[i]) {
                earliestdiff = i;
                break;
            }
        }
        if(earliestdiff != -1) {

            int shift = earliestdiff - earliestb;
            assert(shift);
            ops.push_back(shift);
            if(shift > 0) { 
                bsa ^= bsa << shift;
            } else {
                bsa ^= bsa >> (-shift);
            }
            for(int i = n; i < 2000; i++) {
                bsa[i] = 0;
            }
        } else {
            break;
        }
    }

    cout << ops.size() << '\n';
    for(int i = 0; i < ops.size(); i++) {
        cout << -ops[i] << " \n"[i == ops.size() - 1];
    }

    // cout << "my bitset : ";
    // for(int i = 0; i < n; i++) {
    //     cout << bsa[i];
    // }
    // cout << '\n';
    // cout << "target bitset : ";
    // for(int i = 0; i < n; i++) {
    //     cout << bsb[i];
    // }
    // cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    // cout << "ok\n";

    return 0;
}