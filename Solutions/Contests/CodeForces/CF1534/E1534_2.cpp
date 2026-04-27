#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int debug = 0;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve(int n, int k) {
    if(n % 2 == 1 && k % 2 == 0) {
        cout << "-1\n";
        return;
    }

    vector<int> v(n);
    int tr = 0;

    auto ask = [&](vector<int> a) -> void {
        assert(sz(a) == k);
        cout << "?";
        for(int x : a) {
            cout << " " << x + 1;
            v[x] ^= 1;
        }
        cout << endl;
        int res; 
        if(debug == 0) {
            cin >> res;
        } else {
            res = rng() % 676767;
        }
        tr ^= res;
    };

    int ttfang = 0;

    while(accumulate(v.begin(), v.end(), 0) != n) {
        int sum = accumulate(v.begin(), v.end(), 0);
        int empty = n - sum;
        vector<int> a;
        int zero = 0, one = 0;
        if(empty % k) {

            int f = 0;
            for(int i = k; i >= 0; i--) {
                int nz = k - i;
                int nx_empty = empty + i - nz;
                if(nx_empty % k == 0 && i <= sum && nz <= empty) {
                    f = 1;
                    one = i;
                    zero = nz;
                }
            }

            // cout << "f : " << f << endl;

            if(f == 0) {
                if(ttfang) {
                    zero = min(k, empty);
                    one = k - zero;
                } else {
                    one = min(k, sum);
                    zero = k - one;
                }
            }

        } else {
            zero = k;
            one = 0;
        }

        // cout << "sum : " << sum << " empty : " << empty << endl;
        // cout << "z : " << zero << " o : " << one << endl;

        assert(one <= sum);
        assert(zero <= empty);
        assert(one + zero == k);
        for(int i = 0; i < n; i++) {
            if(v[i] == 0 && zero) {
                a.push_back(i);
                zero--;
            }
            if(v[i] == 1 && one) {
                a.push_back(i);
                one--;
            }
        }

        ttfang ^= 1;

        ask(a);
    }

    cout << "! " << tr << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if(debug == 0) {
        int n, k; cin >> n >> k;
        solve(n, k);
    } else {
        for(int n = 1; n <= 10; n++) {
            for(int k = 1; k <= n; k++) {
                solve(n, k);
            }
        }
    }


    return 0;
}
